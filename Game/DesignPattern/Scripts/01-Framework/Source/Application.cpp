#include "Application.h"

#include <thread>
#include <chrono>

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <imgui.h>
//ImGUI��׼����չ
#include <imgui_stdlib.h>
//ImGUI��SDLʵ��
#include <imgui_impl_sdl.h>
//ImGUI��SDL��Ⱦ��ʵ��
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
	//SDL��ϵͳ��ʼ��
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	//����Ƶ�豸
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//���뷨�༭����IME��������ʾ
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	//����Ӧ�ô���
	window = SDL_CreateWindow(u8"DesignPattern",        //���ڱ���
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //������ʾ
		900, 720,                                       //���ڴ�С
		SDL_WINDOW_ALLOW_HIGHDPI);                      //��DPI��ʾ

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	//��ʼ��ImGUI������
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	//����ImGUI��ʽ
	ImGuiStyle& _style = ImGui::GetStyle();
	//����ֱ��
	_style.WindowRounding = 0.0f;
	//�ؼ��߿��С
	_style.FrameBorderSize = 1.0f;
	//�ؼ�������ɫ
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	//�ؼ���΢Բ��
	_style.FrameRounding = 2.0f;

	//����ImGUI�������
	ImGuiIO& _ioImGui = ImGui::GetIO();
	//����ͣ���Ͷര��
	_ioImGui.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	//����΢���ź���������
	_ioImGui.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\msyh.ttc)", 18.0f, nullptr, _ioImGui.Fonts->GetGlyphRangesChineseFull());

	//������Դ������ģʽʾ��
	ResourcesManager::Instance()->Load(renderer);
	ExampleManager::Instance()->Init(renderer);
}

Application::~Application()
{
	//����ImGUI���
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//����SDL���
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//����SDL��ϵͳ
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Application::Run(int _argc, char** _argv)
{
	#pragma region Time
	//144FPS��ÿ֡����ʱ��
	const std::chrono::nanoseconds _frameDuration(1000000000 / 144);
	//��¼��һ֡ʱ��
	std::chrono::steady_clock::time_point _lastTick = std::chrono::steady_clock::now();
	#pragma endregion

	//��ѭ��
	while (!isQuit)
	{
		#pragma region Input
		SDL_Event _event;
		while (SDL_PollEvent(&_event))
		{
			//ImGUI�����¼�
			ImGui_ImplSDL2_ProcessEvent(&_event);

			//SDL�����¼�
			if (_event.type == SDL_QUIT)
				isQuit = true;

			ExampleManager::Instance()->OnInput(&_event);
		}
		#pragma endregion

		#pragma region Time
		//����֡���ʱ��
		std::chrono::steady_clock::time_point _frameStart = std::chrono::steady_clock::now();
		//������һ֡����ǰ֡��ʱ���
		float _delta = std::chrono::duration<float>(_frameStart - _lastTick).count();
		#pragma endregion

		#pragma region ImGUI
		//׼��ImGUI��֡
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		#pragma endregion

		//���¸����ģʽʾ��������
		ExampleManager::Instance()->OnUpdate(_delta);

		#pragma region Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ExampleManager::Instance()->OnRender();

		//��ȾImGUI
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer);
		#pragma endregion

		#pragma region LimitFPS
		_lastTick = _frameStart;
		//��ѭ�������󣬼���ʣ��ʱ�䲢˯�ߣ���֡�ʿ���
		std::chrono::nanoseconds _sleepDuration = _frameDuration - (std::chrono::steady_clock::now() - _frameStart);
		if (_sleepDuration > std::chrono::nanoseconds(0))
			std::this_thread::sleep_for(_sleepDuration);
		#pragma endregion
	}

	return 0;
}