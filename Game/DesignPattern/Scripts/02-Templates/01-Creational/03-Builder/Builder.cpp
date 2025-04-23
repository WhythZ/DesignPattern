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
	ImGui::TextUnformatted(u8"������");				ImGui::SameLine();
	ImGui::RadioButton(u8"����", &typeWeapon, 0);	ImGui::SameLine();
	ImGui::RadioButton(u8"����", &typeWeapon, 1);	ImGui::SameLine();
	ImGui::RadioButton(u8"����", &typeWeapon, 2);

	ImGui::TextUnformatted(u8"���壺");				ImGui::SameLine();
	ImGui::RadioButton(u8"��ɫ", &typeBody, 0);		ImGui::SameLine();
	ImGui::RadioButton(u8"��ɫ", &typeBody, 1);		ImGui::SameLine();
	ImGui::RadioButton(u8"��ɫ", &typeBody, 2);	

	ImGui::TextUnformatted(u8"ñ�ӣ�");				ImGui::SameLine();
	ImGui::RadioButton(u8"�ʹ�", &typeHat, 0);		ImGui::SameLine();
	ImGui::RadioButton(u8"��ñ", &typeHat, 1);		ImGui::SameLine();
	ImGui::RadioButton(u8"��ñ", &typeHat, 2);
	ImGui::EndGroup();

	ImGui::SameLine();

	ImGui::BeginGroup();
	if (ImGui::Button(u8"��������ɯ�׼�", {ImGui::GetContentRegionAvail().x / 2, 35}))
	{
		elizabethChickenBuilder.InitWeapon();
		elizabethChickenBuilder.InitBody();
		elizabethChickenBuilder.InitHat();
		delete chicken; chicken = elizabethChickenBuilder.Build();
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"������ñ˱ָ��", { ImGui::GetContentRegionAvail().x, 35 }))
	{
		greenHatOriginalRecipeChickenBuilder.InitWeapon();
		greenHatOriginalRecipeChickenBuilder.InitBody();
		greenHatOriginalRecipeChickenBuilder.InitHat();
		delete chicken; chicken = greenHatOriginalRecipeChickenBuilder.Build();
	}
	if (ImGui::Button(u8"����������Զ���ļ��ɣ�", { ImGui::GetContentRegionAvail().x, 40 }))
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