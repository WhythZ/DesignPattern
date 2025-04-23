#include "TemplateMethod.h"

#include <random>

#include <imgui.h>

using namespace _TemplateMethodPattern;

void CustomizedMapGen::OnInspectConfig()
{
	ImGui::SetNextWindowSize({ 320, 285 });
	if (!ImGui::BeginPopup("config_window")) return;

	{
		ImGui::TextDisabled(u8"地形");
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 110);

		ImGui::TextUnformatted(u8"深坑数量："); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::DragInt(u8"##深坑数量", &holeNum, 1.0f, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
		ImGui::NextColumn();

		ImGui::TextUnformatted(u8"地刺数量："); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::DragInt(u8"##地刺数量", &spikesNum, 1.0f, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
		ImGui::NextColumn();

		ImGui::Columns(1);
	}

	ImGui::Separator();
	{
		ImGui::TextDisabled(u8"生物");
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 110);

		ImGui::TextUnformatted(u8"生成精灵："); ImGui::NextColumn();
		ImGui::Checkbox(u8"##生成精灵", &hasNPC);
		ImGui::NextColumn();

		ImGui::TextUnformatted(u8"蜥蜴数量："); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::DragInt(u8"##蜥蜴数量", &lizardNum, 1.0f, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
		ImGui::NextColumn();

		ImGui::TextUnformatted(u8"哥布林数量："); ImGui::NextColumn();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::DragInt(u8"##哥布林数量", &goblinNum, 1.0f, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
		ImGui::NextColumn();

		ImGui::Columns(1);
	}
	ImGui::Separator();
	{
		ImGui::TextDisabled(u8"其他");
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 110);

		ImGui::TextUnformatted(u8"生成出口："); ImGui::NextColumn();
		ImGui::Checkbox(u8"##生成出口", &hasExit);
		ImGui::NextColumn();

		ImGui::TextUnformatted(u8"生成奖励宝箱："); ImGui::NextColumn();
		ImGui::Checkbox(u8"##生成奖励宝箱", &hasReward);	
		ImGui::NextColumn();

		ImGui::Columns(1);
	}

	ImGui::EndPopup();
}

void CustomizedMapGen::GenerateNPC(Map* _map)
{
	if (hasNPC)
	{
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		_map->AddItem(new Elf(), _emptyGridList[rand() % _emptyGridList.size()]);
	}
}

void CustomizedMapGen::GenerateExit(Map* _map)
{
	if (hasExit)
	{
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		_map->AddItem(new Stairs(), _emptyGridList[rand() % _emptyGridList.size()]);
	}
}

void CustomizedMapGen::GenerateTrap(Map* _map)
{
	{
		std::vector<SDL_Point> _targetGridList(holeNum);
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		std::sample(_emptyGridList.begin(), _emptyGridList.end(),
			_targetGridList.begin(), holeNum, std::mt19937(std::random_device()()));
		for (const SDL_Point& _grid : _targetGridList)
			_map->AddItem(new Hole(), _grid);
	}
	{
		std::vector<SDL_Point> _targetGridList(spikesNum);
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		std::sample(_emptyGridList.begin(), _emptyGridList.end(),
			_targetGridList.begin(), spikesNum, std::mt19937(std::random_device()()));
		for (const SDL_Point& _grid : _targetGridList)
			_map->AddItem(new Spikes(), _grid);
	}
}

void CustomizedMapGen::GenerateEnemy(Map* _map)
{
	{
		std::vector<SDL_Point> _targetGridList(goblinNum);
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		std::sample(_emptyGridList.begin(), _emptyGridList.end(),
			_targetGridList.begin(), goblinNum, std::mt19937(std::random_device()()));
		for (const SDL_Point& _grid : _targetGridList)
			_map->AddItem(new Goblin(), _grid);
	}
	{
		std::vector<SDL_Point> _targetGridList(lizardNum);
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		std::sample(_emptyGridList.begin(), _emptyGridList.end(),
			_targetGridList.begin(), lizardNum, std::mt19937(std::random_device()()));
		for (const SDL_Point& _grid : _targetGridList)
			_map->AddItem(new Lizard(), _grid);
	}
}

void CustomizedMapGen::GenerateReward(Map* _map)
{
	if (hasReward)
	{
		const std::vector<SDL_Point>& _emptyGridList = _map->GetEmptyGrids();
		_map->AddItem(new Chest(), _emptyGridList[rand() % _emptyGridList.size()]);
	}
}

TemplateMethodPattern::TemplateMethodPattern(SDL_Renderer* _renderer)
{
	map = mapGenerator.Generate();

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

TemplateMethodPattern::~TemplateMethodPattern()
{
	delete map;

	SDL_DestroyTexture(textureTarget);
}

void TemplateMethodPattern::OnUpdate(float _delta)
{
	map->OnUpdate(_delta);

	if (ImGui::ImageButton(ResourcesManager::Instance()->FindTexture("icon-config"), { 30, 30 }))
		ImGui::OpenPopup("config_window");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextDisabled(u8"点击打开配置面板");
		ImGui::EndTooltip();
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"重新生成关卡地图", { ImGui::GetContentRegionAvail().x, 35 }))
	{
		delete map;
		map = mapGenerator.Generate();
	}

	ImGui::BeginChild("map", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();

	mapGenerator.OnInspectConfig();
}

void TemplateMethodPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 65, 65, 65, 255);
	SDL_RenderClear(_renderer);

	map->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
