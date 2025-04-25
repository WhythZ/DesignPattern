#include "Application.h"

#include <thread>
#include <chrono>

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <imgui.h>
//ImGUI标准库扩展
#include <imgui_stdlib.h>
//ImGUI的SDL实现
#include <imgui_impl_sdl.h>
//ImGUI的SDL渲染器实现
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
	//SDL子系统初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	//打开音频设备
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//输入法编辑器（IME）界面提示
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	//创建应用窗口
	window = SDL_CreateWindow(u8"DesignPattern",        //窗口标题
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, //居中显示
		900, 720,                                       //窗口大小
		SDL_WINDOW_ALLOW_HIGHDPI);                      //高DPI显示

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	//初始化ImGUI上下文
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);

	//配置ImGUI样式
	ImGuiStyle& _style = ImGui::GetStyle();
	//窗口直角
	_style.WindowRounding = 0.0f;
	//控件边框大小
	_style.FrameBorderSize = 1.0f;
	//控件背景颜色
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	//控件轻微圆角
	_style.FrameRounding = 2.0f;

	//设置ImGUI输入输出
	ImGuiIO& _ioImGui = ImGui::GetIO();
	//启用停靠和多窗口
	_ioImGui.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
	//加载微软雅黑中文字体
	_ioImGui.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\msyh.ttc)", 18.0f, nullptr, _ioImGui.Fonts->GetGlyphRangesChineseFull());

	//加载资源与各设计模式示例
	ResourcesManager::Instance()->Load(renderer);
	ExampleManager::Instance()->Init(renderer);
}

Application::~Application()
{
	//销毁ImGUI相关
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	//销毁SDL相关
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//销毁SDL子系统
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Application::Run(int _argc, char** _argv)
{
	#pragma region Time
	//144FPS的每帧持续时间
	const std::chrono::nanoseconds _frameDuration(1000000000 / 144);
	//记录上一帧时刻
	std::chrono::steady_clock::time_point _lastTick = std::chrono::steady_clock::now();
	#pragma endregion

	//主循环
	while (!isQuit)
	{
		#pragma region Input
		SDL_Event _event;
		while (SDL_PollEvent(&_event))
		{
			//ImGUI处理事件
			ImGui_ImplSDL2_ProcessEvent(&_event);

			//SDL处理事件
			if (_event.type == SDL_QUIT)
				isQuit = true;

			ExampleManager::Instance()->OnInput(&_event);
		}
		#pragma endregion

		#pragma region Time
		//计算帧间隔时间
		std::chrono::steady_clock::time_point _frameStart = std::chrono::steady_clock::now();
		//计算上一帧到当前帧的时间差
		float _delta = std::chrono::duration<float>(_frameStart - _lastTick).count();
		#pragma endregion

		#pragma region ImGUI
		//准备ImGUI新帧
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		#pragma endregion

		//更新各设计模式示例的数据
		ExampleManager::Instance()->OnUpdate(_delta);

		#pragma region Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ExampleManager::Instance()->OnRender();

		//渲染ImGUI
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer);
		#pragma endregion

		#pragma region LimitFPS
		_lastTick = _frameStart;
		//主循环结束后，计算剩余时间并睡眠，以帧率控制
		std::chrono::nanoseconds _sleepDuration = _frameDuration - (std::chrono::steady_clock::now() - _frameStart);
		if (_sleepDuration > std::chrono::nanoseconds(0))
			std::this_thread::sleep_for(_sleepDuration);
		#pragma endregion
	}

	return 0;
}