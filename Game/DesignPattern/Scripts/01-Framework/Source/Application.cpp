#include "Application.h"

#include <thread>
#include <chrono>

#include <imgui.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <imgui_stdlib.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include "ExampleManager.h"
#include "ResourceManager.h"

Application* Application::application = nullptr;

Application* Application::Instance()
{
	if (!application)
		application = new Application();
	return application;
}

Application::Application()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	window = SDL_CreateWindow(u8"DesignPattern",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		900, 720, SDL_WINDOW_ALLOW_HIGHDPI);

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	ImGuiStyle& _style = ImGui::GetStyle();
	_style.WindowRounding = 0.0f;
	_style.FrameBorderSize = 1.0f;
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	_style.FrameRounding = 2.0f;
	_style.FrameBorderSize = 1.0f;

	ImGuiIO& _ioImGui = ImGui::GetIO();
	_ioImGui.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	_ioImGui.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\msyh.ttc)", 18.0f, nullptr, _ioImGui.Fonts->GetGlyphRangesChineseFull());

	ResourcesManager::Instance()->Load(renderer);
	ExampleManager::Instance()->Init(renderer);
}

Application::~Application()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Application::Run(int _argc, char** _argv)
{
	using namespace std::chrono;

	const nanoseconds _frameDuration(1000000000 / 144);
	steady_clock::time_point _lastTick = steady_clock::now();

	while (!isQuit)
	{
		SDL_Event _event;
		while (SDL_PollEvent(&_event))
		{
			ImGui_ImplSDL2_ProcessEvent(&_event);

			if (_event.type == SDL_QUIT)
				isQuit = true;

			ExampleManager::Instance()->OnInput(&_event);
		}

		steady_clock::time_point _frameStart = steady_clock::now();
		float _delta = duration<float>(_frameStart - _lastTick).count();

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ExampleManager::Instance()->OnUpdate(_delta);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ExampleManager::Instance()->OnRender();

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer);

		_lastTick = _frameStart;
		nanoseconds _sleepDuration = _frameDuration - (steady_clock::now() - _frameStart);
		if (_sleepDuration > nanoseconds(0))
			std::this_thread::sleep_for(_sleepDuration);
	}

	return 0;
}