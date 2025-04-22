#include "AbstractFactory.h"

#include <imgui.h>

using namespace _AbstractFactoryPattern;

static std::vector<std::vector<const char*>> atlas_path_template_map =
{
	{ "SlimeBlue_0%d", "SlimeGreen_0%d", "SlimeRed_0%d" },
	{ "MegaSlimeBlue_0%d", "MegaSlimeGreen_0%d", "MegaSlimeRed_0%d" },
	{ "KingSlimeBlue_0%d", "KingSlimeGreen_0%d", "KingSlimeRed_0%d" }
};

Slime::Slime(SlimeDefFactory* factory, const Vector2& position)
{
	this->position = position;

	int idx_size = (int)factory->get_size_def()->GetSize();
	int idx_attrbute = (int)factory->get_attribute_def()->get_attribute();

	atlas.Load(atlas_path_template_map[idx_size][idx_attrbute], 6);

	animation.AddFrame(&atlas);
	animation.SetLoop(true);
	animation.SetInterval(0.1f);
}

Slime::~Slime() = default;

AbstractFactoryPattern::AbstractFactoryPattern(SDL_Renderer* renderer)
{
	SmallIceSlimeDefFactory small_ice_slime_def_factory;
	MediumIceSlimeDefFactory medium_ice_slime_def_factory;
	LargeIceSlimeDefFactory large_ice_slime_def_factory;
	SmallGrassSlimeDefFactory small_grass_slime_def_factory;
	MediumGrassSlimeDefFactory medium_grass_slime_def_factory;
	LargeGrassSlimeDefFactory large_grass_slime_def_factory;
	SmallFireSlimeDefFactory small_fire_slime_def_factory;
	MediumFireSlimeDefFactory medium_fire_slime_def_factory;
	LargeFireSlimeDefFactory large_fire_slime_def_factory;

	slime_list.push_back(new Slime(&small_ice_slime_def_factory,	{ 200, 110 }));
	slime_list.push_back(new Slime(&small_grass_slime_def_factory,	{ 200, 310 }));
	slime_list.push_back(new Slime(&small_fire_slime_def_factory,	{ 200, 510 }));
	slime_list.push_back(new Slime(&medium_ice_slime_def_factory,	{ 350, 110 }));
	slime_list.push_back(new Slime(&medium_grass_slime_def_factory,	{ 350, 310 }));
	slime_list.push_back(new Slime(&medium_fire_slime_def_factory,	{ 350, 510 }));	
	slime_list.push_back(new Slime(&large_ice_slime_def_factory,	{ 500, 100 }));
	slime_list.push_back(new Slime(&large_grass_slime_def_factory,	{ 500, 300 }));
	slime_list.push_back(new Slime(&large_fire_slime_def_factory,	{ 500, 500 }));

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

AbstractFactoryPattern::~AbstractFactoryPattern()
{
	SDL_DestroyTexture(textureTarget);

	for (Slime* slime : slime_list)
		delete slime;
}

void AbstractFactoryPattern::OnUpdate(float delta)
{
	for (Slime* slime : slime_list)
		slime->OnUpdate(delta);

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
}

void AbstractFactoryPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	for (Slime* slime : slime_list)
		slime->OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}