#include "Prototype.h"

#include <imgui.h>
#include <SDL_mixer.h>

using namespace _PrototypePattern;

static int typeWeapon = 0, typeBody = 0, typeHat = 0;

PrototypePattern::PrototypePattern(SDL_Renderer* _renderer)
{
	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 665, 590);

	atlasWeaponFork.Load("weapon_fork_%d", 8);
	atlasWeaponPlate.Load("weapon_plate_%d", 8);
	atlasWeaponSpoon.Load("weapon_spoon_%d", 8);

	atlasBodyBrown.Load("brown_chicken_%d", 8);
	atlasBodyRed.Load("red_chicken_%d", 8);
	atlasBodyWhite.Load("white_chicken_%d", 8);

	atlasHatCrown.Load("crown_%d", 8);
	atlasHatGreen.Load("green_hat_%d", 8);
	atlasHatStraw.Load("straw_hat_%d", 8);
}

PrototypePattern::~PrototypePattern()
{
	SDL_DestroyTexture(textureTarget);
}

void PrototypePattern::OnEnter()
{
	srand((unsigned int)time(NULL));
	prototypeChicken = new Chicken();
}

void PrototypePattern::OnExit()
{
	for (Chicken* _chicken : chickenList)
		delete _chicken;
	chickenList.clear();

	delete prototypeChicken; prototypeChicken = nullptr;
}

void PrototypePattern::OnUpdate(float _delta)
{
	for (Chicken* _chicken : chickenList)
		_chicken->OnUpdate(_delta);

	ImGui::BeginGroup();
	ImGui::TextUnformatted(u8"武器：");				ImGui::SameLine();
	ImGui::RadioButton(u8"叉子", &typeWeapon, 0);	ImGui::SameLine();
	ImGui::RadioButton(u8"盘子", &typeWeapon, 1);	ImGui::SameLine();
	ImGui::RadioButton(u8"汤匙", &typeWeapon, 2);

	ImGui::TextUnformatted(u8"身体：");				ImGui::SameLine();
	ImGui::RadioButton(u8"棕色", &typeBody, 0);		ImGui::SameLine();
	ImGui::RadioButton(u8"红色", &typeBody, 1);		ImGui::SameLine();
	ImGui::RadioButton(u8"白色", &typeBody, 2);	

	ImGui::TextUnformatted(u8"帽子：");				ImGui::SameLine();
	ImGui::RadioButton(u8"皇冠", &typeHat, 0);		ImGui::SameLine();
	ImGui::RadioButton(u8"绿帽", &typeHat, 1);		ImGui::SameLine();
	ImGui::RadioButton(u8"草帽", &typeHat, 2);
	ImGui::EndGroup();

	ImGui::SameLine();

	if (ImGui::Button(u8"将当前属性的鸡生成到世界中", { ImGui::GetContentRegionAvail().x, 80 }))
	{
		switch (typeWeapon)
		{
		case 0: prototypeChicken->SetWeapon(&atlasWeaponFork); break;
		case 1: prototypeChicken->SetWeapon(&atlasWeaponPlate); break;
		case 2: prototypeChicken->SetWeapon(&atlasWeaponFork); break;
		}
		switch (typeBody)
		{
		case 0: prototypeChicken->SetBody(&atlasBodyBrown); break;
		case 1: prototypeChicken->SetBody(&atlasBodyRed); break;
		case 2: prototypeChicken->SetBody(&atlasBodyWhite); break;
		}
		switch (typeHat)
		{
		case 0: prototypeChicken->SetHat(&atlasHatCrown); break;
		case 1: prototypeChicken->SetHat(&atlasHatGreen); break;
		case 2: prototypeChicken->SetHat(&atlasHatStraw); break;
		}
		chickenList.push_back(prototypeChicken->Clone());
		Mix_PlayChannel(-1, ResourcesManager::Instance()->findAudio("click"), 0);
	}

	ImGui::BeginChild("chicken_result", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Border);
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void PrototypePattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	for (Chicken* _chicken : chickenList)
		_chicken->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
