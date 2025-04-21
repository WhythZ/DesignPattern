#include "ExampleManager.h"
#include <Windows.h>
#include <imgui.h>
#include "ResourceManager.h"

#include "../../02-Templates/01-Creational/01-FactoryMethod/FactoryMethod.h"
#include "../../02-Templates/01-Creational/02-AbstractFactory/AbstractFactory.h"
#include "../../02-Templates/01-Creational/03-Builder/Builder.h"
#include "../../02-Templates/01-Creational/04-Prototype/Prototype.h"
#include "../../02-Templates/01-Creational/05-Singleton/Singleton.h"

#include "../../02-Templates/02-Structural/01-Adapter/Adapter.h"
#include "../../02-Templates/02-Structural/02-Bridge/Bridge.h"
#include "../../02-Templates/02-Structural/03-Composite/Composite.h"
#include "../../02-Templates/02-Structural/04-Decorator/Decorator.h"
#include "../../02-Templates/02-Structural/05-Facade/Facade.h"
#include "../../02-Templates/02-Structural/06-Flyweight/Flyweight.h"
#include "../../02-Templates/02-Structural/07-Proxy/Proxy.h"

#include "../../02-Templates/03-Behavioral/01-ChainOfResonsibility/ChainOfResponsibility.h"
#include "../../02-Templates/03-Behavioral/02-Command/Command.h"
#include "../../02-Templates/03-Behavioral/03-Iterator/Iterator.h"
#include "../../02-Templates/03-Behavioral/04-Mediator/Mediator.h"
#include "../../02-Templates/03-Behavioral/05-Memento/Memento.h"
#include "../../02-Templates/03-Behavioral/06-Observer/Observer.h"
#include "../../02-Templates/03-Behavioral/07-State/State.h"
#include "../../02-Templates/03-Behavioral/08-Strategy/Strategy.h"
#include "../../02-Templates/03-Behavioral/09-TemplateMethod/TemplateMethod.h"
#include "../../02-Templates/03-Behavioral/10-Visitor/Visitor.h"
#include "../../02-Templates/03-Behavioral/11-Interpreter/Interpreter.h"

ExampleManager* ExampleManager::manager = nullptr;

ExampleManager* ExampleManager::Instance()
{
	if (!manager)
		manager = new ExampleManager();
	return manager;
}

ExampleManager::~ExampleManager()
{
	if (current_example)
		current_example->on_exit();

	for (auto& pair : example_pool)
		delete pair.second;
}

void ExampleManager::Init(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	texture_target = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
	SDL_SetTextureBlendMode(texture_target, SDL_BLENDMODE_BLEND);

	subject_creational.title = u8"一、创建型模式（5）";
	SDL_Texture* texture_icon_creational = ResourcesManager::Instance()->findTexture("icon-creational");
	AddExample(subject_creational, MenuItem("factory_method", texture_icon_creational, u8"1. 工厂方法模式"), new FactoryMethodPattern(renderer));
	AddExample(subject_creational, MenuItem("abstract_factory", texture_icon_creational, u8"2. 抽象工厂模式"), new AbstractFactoryPattern(renderer));
	AddExample(subject_creational, MenuItem("builder", texture_icon_creational, u8"3. 建造者模式"), new BuilderPattern(renderer));
	AddExample(subject_creational, MenuItem("prototype", texture_icon_creational, u8"4. 原型模式"), new PrototypePattern(renderer));
	AddExample(subject_creational, MenuItem("singleton", texture_icon_creational, u8"5. 单例模式"), new SingletonPattern(renderer));

	subject_structural.title = u8"二、结构型模式（7）";
	SDL_Texture* texture_icon_structural = ResourcesManager::Instance()->findTexture("icon-structural");
	AddExample(subject_structural, MenuItem("adapter", texture_icon_structural, u8"1. 适配器模式"), new AdapterPattern(renderer));
	AddExample(subject_structural, MenuItem("bridge", texture_icon_structural, u8"2. 桥接模式"), new BridgePattern());
	AddExample(subject_structural, MenuItem("composite", texture_icon_structural, u8"3. 组合模式"), new CompositePattern(renderer));
	AddExample(subject_structural, MenuItem("decorator", texture_icon_structural, u8"4. 装饰器模式"), new DecoratorPattern(renderer));
	AddExample(subject_structural, MenuItem("facade", texture_icon_structural, u8"5. 外观模式"), new FacadePattern());
	AddExample(subject_structural, MenuItem("flyweight", texture_icon_structural, u8"6. 享元模式"), new FlyweightPattern());
	AddExample(subject_structural, MenuItem("proxy", texture_icon_structural, u8"7. 代理模式"), new ProxyPattern(renderer));

	subject_behavioral.title = u8"三、行为模式（11）";
	SDL_Texture* texture_icon_behavioral = ResourcesManager::Instance()->findTexture("icon-behavioral");
	AddExample(subject_behavioral, MenuItem("chain_of_responsibility", texture_icon_behavioral, u8"1. 责任链模式"), new ChainOfResponsibilityPattern());
	AddExample(subject_behavioral, MenuItem("command", texture_icon_behavioral, u8"2. 命令模式"), new CommandPattern(renderer));
	AddExample(subject_behavioral, MenuItem("iterator", texture_icon_behavioral, u8"3. 迭代器模式"), new IteratorPattern(renderer));
	AddExample(subject_behavioral, MenuItem("mediator", texture_icon_behavioral, u8"4. 中介者模式"), new MediatorPattern());
	AddExample(subject_behavioral, MenuItem("memento", texture_icon_behavioral, u8"5. 备忘录模式"), new MementoPattern(renderer));
	AddExample(subject_behavioral, MenuItem("observer", texture_icon_behavioral, u8"6. 观察者模式"), new ObserverPattern());
	AddExample(subject_behavioral, MenuItem("state", texture_icon_behavioral, u8"7. 状态模式"), new StatePattern(renderer));
	AddExample(subject_behavioral, MenuItem("strategy", texture_icon_behavioral, u8"8. 策略模式"), new StrategyPattern(renderer));
	AddExample(subject_behavioral, MenuItem("template_method", texture_icon_behavioral, u8"9. 模板方法模式"), new TemplateMethodPattern(renderer));
	AddExample(subject_behavioral, MenuItem("visitor", texture_icon_behavioral, u8"10. 访问者模式"), new VisitorPattern());
	AddExample(subject_behavioral, MenuItem("interpreter", texture_icon_behavioral, u8"11. 解释器模式"), new InterpreterPattern(renderer));
}

void ExampleManager::OnInput(const SDL_Event* event)
{
	if (!current_example) return;

	current_example->OnInput(event);
}

void ExampleManager::OnUpdate(float delta)
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	static const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoSavedSettings;

	ImGui::Begin("main_window", nullptr, flags);

	static const ImVec2 size_menu = { 180, ImGui::GetContentRegionAvail().y };
	{
		ImGui::BeginChild("menu", size_menu, ImGuiChildFlags_Border);
		OnUpdateSubject(subject_creational);
		OnUpdateSubject(subject_structural);
		OnUpdateSubject(subject_behavioral);
		ImGui::EndChild();
	}

	ImGui::SameLine();

	static const ImVec2 size_stage = ImGui::GetContentRegionAvail();
	{
		ImGui::BeginChild("stage", size_stage, ImGuiChildFlags_Border);
		if (current_example)
			current_example->OnUpdate(delta);
		else
			OnUpdateBlankContent();
		ImGui::EndChild();
	}

	ImGui::End();
}

void ExampleManager::OnRender()
{
	if (!current_example) return;

	current_example->OnRender(renderer);
}

void ExampleManager::OnUpdateBlankContent()
{
	ImGui::SetCursorPos({ 545, 665 });
	ImGui::TextDisabled(u8"HiHi~"); ImGui::SameLine();
	if (ImGui::ImageButton(ResourcesManager::Instance()->findTexture("icon-bilibili"), { 14, 14 }))
		ShellExecute(NULL, TEXT("open"), TEXT("https://bilibili.com"), NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextDisabled(u8"点击打开我的 Bilibili 主页 ~");
		ImGui::EndTooltip();
	}
}

void ExampleManager::OnUpdateSubject(const Subject& subject)
{
	if (ImGui::CollapsingHeader(subject.title.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (const MenuItem& menu_item : subject.item_list)
		{
			static const ImVec2 size_icon = 
			{ 
				ImGui::GetTextLineHeightWithSpacing(), 
				ImGui::GetTextLineHeightWithSpacing() 
			};

			ImGui::Image(menu_item.icon, size_icon); ImGui::SameLine();
			if (ImGui::Selectable(menu_item.title.c_str(), current_example_id == menu_item.id))
				SwitchTo(menu_item.id);
		}
	}
}

void ExampleManager::SwitchTo(const std::string& id)
{
	if (current_example)
		current_example->on_exit();

	current_example_id = id;
	current_example = example_pool[id];

	if (current_example)
		current_example->on_enter();
}

void ExampleManager::AddExample(Subject& subject, const MenuItem& menu_item, Example* example)
{
	subject.item_list.emplace_back(menu_item);
	example_pool[menu_item.id] = example;
}