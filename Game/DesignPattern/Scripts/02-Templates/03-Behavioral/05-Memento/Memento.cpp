#include "Memento.h"

#include <imgui.h>
#include <fstream>
#include <sstream>

using namespace _MementoPattern;

MementoPattern::MementoPattern(SDL_Renderer* _renderer)
{
	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 384, 384);
}

MementoPattern::~MementoPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void MementoPattern::OnInput(const SDL_Event* _event)
{
	player.OnInput(_event);
	mySwitch.OnInput(_event);
}

void MementoPattern::OnUpdate(float _delta)
{
	player.OnUpdate(_delta);

	if (ImGui::Button(u8"加载 \"Data/Save.json\" 存档文件到场景", { ImGui::GetContentRegionAvail().x / 2, 35 }))
		LoadScene();
	ImGui::SameLine();
	if (ImGui::Button(u8"保存场景到 \"Data/Save.json\" 存档文件", { ImGui::GetContentRegionAvail().x, 35 }))
		DumpScene();

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::SetCursorPos({ 10, 10 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用[上/下/左/右]方向键控制角色移动，使用[空格键]切换拉杆开关状态");
	ImGui::EndChild();
}

void MementoPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	SDL_RenderCopy(_renderer, ResourcesManager::Instance()->FindTexture("tidy_room"), nullptr, nullptr);
	mySwitch.OnRender(_renderer); player.OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}

void MementoPattern::LoadScene()
{
	std::ifstream _file("Data/Save.json");
	if (!_file.good()) return;

	std::stringstream _strStream;
	_strStream << _file.rdbuf(); _file.close();

	cJSON* _jsonRoot = cJSON_Parse(_strStream.str().c_str());
	if (!_jsonRoot) return;

	player.Load(cJSON_GetObjectItem(_jsonRoot, "player"));
	mySwitch.Load(cJSON_GetObjectItem(_jsonRoot, "switch"));

	cJSON_Delete(_jsonRoot);
}

void MementoPattern::DumpScene()
{
	std::ofstream _file("data/save.json");
	if (!_file.good()) return;

	cJSON* _jsonRoot = cJSON_CreateObject();

	cJSON_AddItemToObject(_jsonRoot, "player", player.Dump());
	cJSON_AddItemToObject(_jsonRoot, "switch", mySwitch.Dump());

	char* _strJson = cJSON_Print(_jsonRoot);
	_file << _strJson; _file.flush(); _file.close();

	free(_strJson);
	cJSON_Delete(_jsonRoot);
}
