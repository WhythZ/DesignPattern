#include "AbstractFactory.h"

#include <imgui.h>

using namespace _AbstractFactoryPattern;

static std::vector<std::vector<const char*>> atlasPathTemplateMap =
{
	{ "SlimeBlue_0%d", "SlimeGreen_0%d", "SlimeRed_0%d" },
	{ "MegaSlimeBlue_0%d", "MegaSlimeGreen_0%d", "MegaSlimeRed_0%d" },
	{ "KingSlimeBlue_0%d", "KingSlimeGreen_0%d", "KingSlimeRed_0%d" }
};

Slime::Slime(SlimeDefFactory* _factory, const Vector2& _position)
{
	position = _position;

	int _idxSize = (int)_factory->GetSizeDef()->GetSize();
	int _idxAttrbute = (int)_factory->GetAttributeDef()->GetAttribute();

	atlas.Load(atlasPathTemplateMap[_idxSize][_idxAttrbute], 6);

	animation.AddFrame(&atlas);
	animation.SetLoop(true);
	animation.SetInterval(0.1f);
}

AbstractFactoryPattern::AbstractFactoryPattern(SDL_Renderer* _renderer)
{
	SmallIceSlimeDefFactory _smallIceSlimeDefFactory;
	MediumIceSlimeDefFactory _mediumIceSlimeDefFactory;
	LargeIceSlimeDefFactory _largeIceSlimeDefFactory;
	SmallGrassSlimeDefFactory _smallGrassSlimeDefFactory;
	MediumGrassSlimeDefFactory _mediumGrassSlimeDefFactory;
	LargeGrassSlimeDefFactory _largeGrassSlimeDefFactory;
	SmallFireSlimeDefFactory _smallFireSlimeDefFactory;
	MediumFireSlimeDefFactory _mediumFireSlimeDefFactory;
	LargeFireSlimeDefFactory _largeFireSlimeDefFactory;

	slimeList.push_back(new Slime(&_smallIceSlimeDefFactory,	{ 200, 110 }));
	slimeList.push_back(new Slime(&_smallGrassSlimeDefFactory,	{ 200, 310 }));
	slimeList.push_back(new Slime(&_smallFireSlimeDefFactory,	{ 200, 510 }));
	slimeList.push_back(new Slime(&_mediumIceSlimeDefFactory,	{ 350, 110 }));
	slimeList.push_back(new Slime(&_mediumGrassSlimeDefFactory,	{ 350, 310 }));
	slimeList.push_back(new Slime(&_mediumFireSlimeDefFactory,	{ 350, 510 }));	
	slimeList.push_back(new Slime(&_largeIceSlimeDefFactory,	{ 500, 100 }));
	slimeList.push_back(new Slime(&_largeGrassSlimeDefFactory,	{ 500, 300 }));
	slimeList.push_back(new Slime(&_largeFireSlimeDefFactory,	{ 500, 500 }));

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

AbstractFactoryPattern::~AbstractFactoryPattern()
{
	SDL_DestroyTexture(textureTarget);

	for (Slime* _slime : slimeList)
		delete _slime;
}

void AbstractFactoryPattern::OnUpdate(float _delta)
{
	for (Slime* _slime : slimeList)
		_slime->OnUpdate(_delta);

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
}

void AbstractFactoryPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	for (Slime* _slime : slimeList)
		_slime->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}