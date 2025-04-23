#include "Proxy.h"

#include <imgui.h>
#include <imgui_stdlib.h>

#include "ResourceManager.h"

ProxyPattern::ProxyPattern(SDL_Renderer* _renderer)
{
	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 664, 548);
}

ProxyPattern::~ProxyPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void ProxyPattern::OnUpdate(float _delta)
{
	ImGui::TextUnformatted(u8"文本："); ImGui::SameLine();
	if (ImGui::InputText(u8"##文本", &strText))
		needUpdate = true;
	ImGui::TextUnformatted(u8"颜色："); ImGui::SameLine();
	if (ImGui::ColorEdit4(u8"##颜色", colorText, ImGuiColorEditFlags_AlphaPreview))
		needUpdate = true;
	ImGui::TextUnformatted(u8"字号："); ImGui::SameLine();
	if (ImGui::DragInt(u8"##字号", &fontSize, 1.0f, 10, 500, "%d px", ImGuiSliderFlags_AlwaysClamp))
		needUpdate = true;
	
	ImGui::Dummy({ 0, 5 });

	ImGui::TextDisabled(u8"此外另见Framework/FontWrapper.h中的代码实现");

	ImGui::Dummy({ 0, 5 });

	ImGui::BeginChild("render_result", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Border);
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void ProxyPattern::OnRender(SDL_Renderer* _renderer)
{
	if (needUpdate)
	{
		UpdateTextureText(_renderer);
		needUpdate = false;
	}

	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 51, 76, 76, 255);
	SDL_RenderClear(_renderer);

	SDL_RenderCopy(_renderer, textureText, nullptr, &rectText);

	SDL_SetRenderTarget(_renderer, nullptr);
}

void ProxyPattern::UpdateTextureText(SDL_Renderer* _renderer)
{
	SDL_DestroyTexture(textureText); textureText = nullptr;

	SDL_Color _color = 
	{ 
		(Uint8)(colorText[0] * 255), (Uint8)(colorText[1] * 255), 
		(Uint8)(colorText[2] * 255), (Uint8)(colorText[3] * 255) 
	};
	SDL_Surface* _surface = TTF_RenderUTF8_Blended(ResourcesManager::Instance()
		->FindFont("SarasaMonoSC-Regular")->GetFont(fontSize), strText.c_str(), _color);
	if (!_surface) return;

	textureText = SDL_CreateTextureFromSurface(_renderer, _surface);
	rectText.w = _surface->w, rectText.h = _surface->h;
	SDL_FreeSurface(_surface);
}
