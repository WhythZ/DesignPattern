#include "Iterator.h"

#include <imgui.h>

using namespace _IteratorPattern;

IteratorPattern::IteratorPattern(SDL_Renderer* _renderer)
{
	for (int i = 0; i < 2; i++)
		itemList.push_back(new MagicBook());
	for (int i = 0; i < 4; i++)
		itemList.push_back(new OrdinaryPotion());
	for (int i = 0; i < 5; i++)
		itemList.push_back(new Coins());
	for (int i = 0; i < 2; i++)
		itemList.push_back(new Scrolls());
	for (int i = 0; i < 6; i++)
		itemList.push_back(new Stick());
	for (int i = 0; i < 8; i++)
		itemList.push_back(new Stone());

	currentIterator = new RandomIterator(itemList);

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 360, 190);
}

IteratorPattern::~IteratorPattern()
{
	for (Item* _item : itemList)
		delete _item;

	SDL_DestroyTexture(textureTarget);
}

void IteratorPattern::OnUpdate(float _delta)
{
	ImGui::Dummy({ 0, 15 });

	OnUpdateSample(&sampleMagicBook);		ImGui::SameLine();
	OnUpdateSample(&sampleOrdinaryPotion);	ImGui::SameLine();
	OnUpdateSample(&sampleCoins);
	OnUpdateSample(&sampleScrolls);			ImGui::SameLine();
	OnUpdateSample(&sampleStick);			ImGui::SameLine();
	OnUpdateSample(&sampleStone);

	ImGui::Dummy({ 0, 50 });

	if (ImGui::Button(u8"随机排序", { ImGui::GetContentRegionAvail().x / 3.0f, 35 }))
	{
		delete currentIterator;
		currentIterator = new RandomIterator(itemList);
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"按类型排序", { ImGui::GetContentRegionAvail().x / 2.0f, 35 }))
	{
		delete currentIterator;
		currentIterator = new TypeSortIterator(itemList);
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"按品质排序", { ImGui::GetContentRegionAvail().x, 35 }))
	{
		delete currentIterator;
		currentIterator = new GradeSortIterator(itemList);
	}

	ImGui::Dummy({ 0, 50 });

	ImGui::BeginChild("backpack", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void IteratorPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 65, 65, 65, 255);
	SDL_RenderClear(_renderer);

	SDL_RenderCopy(_renderer, ResourcesManager::Instance()->FindTexture("backpack"), nullptr, nullptr);

	currentIterator->Reset();
	while (currentIterator->HasNext())
	{
		int _idx = currentIterator->GetIdx();
		Item* _item = currentIterator->Next();

		SDL_Rect _rect = 
		{ 
			38 + (_idx % 8) * 40 - 32 / 2, 
			34 + (_idx / 8) * 40 - 32 / 2,
			32, 32 
		};
		SDL_RenderCopy(_renderer, _item->GetTexture(), nullptr, &_rect);
	}

	SDL_SetRenderTarget(_renderer, nullptr);
}

void IteratorPattern::OnUpdateSample(Item* _item)
{
	static const char* _typeName[3] = { u8"材料", u8"道具", u8"货币" };
	static const char* _gradeName[3] = { u8"平凡", u8"稀有", u8"传说" };

	ImGui::Image(_item->GetTexture(), { 64, 64 }, { 0, 0 }, { 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 0.75f });
	ImGui::SameLine();
	{
		ImGui::BeginGroup();
		ImGui::Text(u8"< %s >", _item->GetName().c_str());
		ImGui::TextUnformatted(u8"类型："); ImGui::SameLine();
		ImGui::TextDisabled(_typeName[(int)_item->GetType()]);
		ImGui::TextUnformatted(u8"品质："); ImGui::SameLine();
		ImGui::TextDisabled(_gradeName[(int)_item->GetGrade()]);
		ImGui::EndGroup();
	}
	ImGui::SameLine();
	ImGui::Dummy({ 65, 0 });
}
