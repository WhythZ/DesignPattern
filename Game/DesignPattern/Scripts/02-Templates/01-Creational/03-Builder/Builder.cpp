#include "Builder.h"

#include <imgui.h>

using namespace _BuilderPattern;

static int typeWeapon = 0, typeBody = 0, typeHat = 0;

void CustomChickenBuilder::InitWeapon()
{
	atlasWeapon.Clear();

	switch (typeWeapon)
	{
	case 0: atlasWeapon.Load("weapon_fork_%d", 8); break;
	case 1: atlasWeapon.Load("weapon_plate_%d", 8); break;
	case 2: atlasWeapon.Load("weapon_spoon_%d", 8); break;
	}
}

void CustomChickenBuilder::InitBody()
{
	atlasBody.Clear();

	switch (typeBody)
	{
	case 0: atlasBody.Load("brown_chicken_%d", 8); break;
	case 1: atlasBody.Load("red_chicken_%d", 8); break;
	case 2: atlasBody.Load("white_chicken_%d", 8); break;
	}
}

void CustomChickenBuilder::InitHat()
{
	atlasHat.Clear();

	switch (typeHat)
	{
	case 0: atlasHat.Load("crown_%d", 8); break;
	case 1: atlasHat.Load("green_hat_%d", 8); break;
	case 2: atlasHat.Load("straw_hat_%d", 8); break;
	}
}

Chicken* CustomChickenBuilder::Build()
{
	Chicken* _chicken = new Chicken();

	_chicken->SetWeapon(&atlasWeapon);
	_chicken->SetBody(&atlasBody);
	_chicken->SetHat(&atlasHat);

	return _chicken;
}

BuilderPattern::BuilderPattern(SDL_Renderer* _renderer)
{
	delete chicken;

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 332, 296);
}

BuilderPattern::~BuilderPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void BuilderPattern::OnUpdate(float _delta)
{
	if (chicken) 
		chicken->OnUpdate(_delta);

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

	ImGui::BeginGroup();
	if (ImGui::Button(u8"生成伊丽莎白鸡", {ImGui::GetContentRegionAvail().x / 2, 35}))
	{
		elizabethChickenBuilder.InitWeapon();
		elizabethChickenBuilder.InitBody();
		elizabethChickenBuilder.InitHat();
		delete chicken; chicken = elizabethChickenBuilder.Build();
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"生成绿帽吮指鸡", { ImGui::GetContentRegionAvail().x, 35 }))
	{
		greenHatOriginalRecipeChickenBuilder.InitWeapon();
		greenHatOriginalRecipeChickenBuilder.InitBody();
		greenHatOriginalRecipeChickenBuilder.InitHat();
		delete chicken; chicken = greenHatOriginalRecipeChickenBuilder.Build();
	}
	if (ImGui::Button(u8"点击生成你自定义的鸡吧！", { ImGui::GetContentRegionAvail().x, 40 }))
	{
		customChickenBuilder.InitWeapon();
		customChickenBuilder.InitBody();
		customChickenBuilder.InitHat();
		delete chicken; chicken = customChickenBuilder.Build();
	}
	ImGui::EndGroup();

	ImGui::BeginChild("chicken_result", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Border);
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void BuilderPattern::OnRender(SDL_Renderer* _renderer)
{
	if (!chicken) return;
	
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	chicken->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}