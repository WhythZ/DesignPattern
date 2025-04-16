#include "example_manager.h"
#include "resources_manager.h"

#include "../../02-Templates/1.factory_method.h"
#include "../../02-Templates/2.abstract_factory.h"
#include "../../02-Templates/3.builder.h"
#include "../../02-Templates/4.prototype.h"
#include "../../02-Templates/5.singleton.h"

#include "../../02-Templates/1.adapter.h"
#include "../../02-Templates/2.bridge.h"
#include "../../02-Templates/3.composite.h"
#include "../../02-Templates/4.decorator.h"
#include "../../02-Templates/5.facade.h"
#include "../../02-Templates/6.flyweight.h"
#include "../../02-Templates/7.proxy.h"

#include "../../02-Templates/1.chain_of_responsibility.h"
#include "../../02-Templates/2.command.h"
#include "../../02-Templates/3.iterator.h"
#include "../../02-Templates/4.mediator.h"
#include "../../02-Templates/5.memento.h"
#include "../../02-Templates/6.observer.h"
#include "../../02-Templates/7.state.h"
#include "../../02-Templates/8.strategy.h"
#include "../../02-Templates/9.template_method.h"
#include "../../02-Templates/10.visitor.h"
#include "../../02-Templates/11.interpreter.h"

#include <imgui.h>

#include <Windows.h>

ExampleManager* ExampleManager::manager = nullptr;

void ExampleManager::init(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	texture_target = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
	SDL_SetTextureBlendMode(texture_target, SDL_BLENDMODE_BLEND);

	subject_creational.title = u8"һ��������ģʽ��5��";
	SDL_Texture* texture_icon_creational = ResourcesManager::instance()->find_texture("icon-creational");
	add_example(subject_creational, MenuItem("factory_method", texture_icon_creational, u8"1. ��������ģʽ"), new FactoryMethodPattern(renderer));
	add_example(subject_creational, MenuItem("abstract_factory", texture_icon_creational, u8"2. ���󹤳�ģʽ"), new AbstractFactoryPattern(renderer));
	add_example(subject_creational, MenuItem("builder", texture_icon_creational, u8"3. ������ģʽ"), new BuilderPattern(renderer));
	add_example(subject_creational, MenuItem("prototype", texture_icon_creational, u8"4. ԭ��ģʽ"), new PrototypePattern(renderer));
	add_example(subject_creational, MenuItem("singleton", texture_icon_creational, u8"5. ����ģʽ"), new SingletonPattern(renderer));

	subject_structural.title = u8"�����ṹ��ģʽ��7��";
	SDL_Texture* texture_icon_structural = ResourcesManager::instance()->find_texture("icon-structural");
	add_example(subject_structural, MenuItem("adapter", texture_icon_structural, u8"1. ������ģʽ"), new AdapterPattern(renderer));
	add_example(subject_structural, MenuItem("bridge", texture_icon_structural, u8"2. �Ž�ģʽ"), new BridgePattern());
	add_example(subject_structural, MenuItem("composite", texture_icon_structural, u8"3. ���ģʽ"), new CompositePattern(renderer));
	add_example(subject_structural, MenuItem("decorator", texture_icon_structural, u8"4. װ����ģʽ"), new DecoratorPattern(renderer));
	add_example(subject_structural, MenuItem("facade", texture_icon_structural, u8"5. ���ģʽ"), new FacadePattern());
	add_example(subject_structural, MenuItem("flyweight", texture_icon_structural, u8"6. ��Ԫģʽ"), new FlyweightPattern());
	add_example(subject_structural, MenuItem("proxy", texture_icon_structural, u8"7. ����ģʽ"), new ProxyPattern(renderer));

	subject_behavioral.title = u8"������Ϊģʽ��11��";
	SDL_Texture* texture_icon_behavioral = ResourcesManager::instance()->find_texture("icon-behavioral");
	add_example(subject_behavioral, MenuItem("chain_of_responsibility", texture_icon_behavioral, u8"1. ������ģʽ"), new ChainOfResponsibilityPattern());
	add_example(subject_behavioral, MenuItem("command", texture_icon_behavioral, u8"2. ����ģʽ"), new CommandPattern(renderer));
	add_example(subject_behavioral, MenuItem("iterator", texture_icon_behavioral, u8"3. ������ģʽ"), new IteratorPattern(renderer));
	add_example(subject_behavioral, MenuItem("mediator", texture_icon_behavioral, u8"4. �н���ģʽ"), new MediatorPattern());
	add_example(subject_behavioral, MenuItem("memento", texture_icon_behavioral, u8"5. ����¼ģʽ"), new MementoPattern(renderer));
	add_example(subject_behavioral, MenuItem("observer", texture_icon_behavioral, u8"6. �۲���ģʽ"), new ObserverPattern());
	add_example(subject_behavioral, MenuItem("state", texture_icon_behavioral, u8"7. ״̬ģʽ"), new StatePattern(renderer));
	add_example(subject_behavioral, MenuItem("strategy", texture_icon_behavioral, u8"8. ����ģʽ"), new StrategyPattern(renderer));
	add_example(subject_behavioral, MenuItem("template_method", texture_icon_behavioral, u8"9. ģ�巽��ģʽ"), new TemplateMethodPattern(renderer));
	add_example(subject_behavioral, MenuItem("visitor", texture_icon_behavioral, u8"10. ������ģʽ"), new VisitorPattern());
	add_example(subject_behavioral, MenuItem("interpreter", texture_icon_behavioral, u8"11. ������ģʽ"), new InterpreterPattern(renderer));
}

void ExampleManager::on_update_blank_content()
{
	ImGui::SetCursorPos({ 545, 665 });
	ImGui::TextDisabled(u8"HiHi~"); ImGui::SameLine();
	if (ImGui::ImageButton(ResourcesManager::instance()->find_texture("icon-bilibili"), { 14, 14 }))
		ShellExecute(NULL, TEXT("open"), TEXT("https://bilibili.com"), NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextDisabled(u8"������ҵ� Bilibili ��ҳ ~");
		ImGui::EndTooltip();
	}
}

void ExampleManager::switch_to(const std::string& id)
{
	if (current_example)
		current_example->on_exit();

	current_example_id = id;
	current_example = example_pool[id];

	if (current_example)
		current_example->on_enter();
}

void ExampleManager::on_input(const SDL_Event* event)
{
	if (!current_example) return;

	current_example->on_input(event);
}

void ExampleManager::on_update(float delta)
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
		on_update_subject(subject_creational);
		on_update_subject(subject_structural);
		on_update_subject(subject_behavioral);
		ImGui::EndChild();
	}

	ImGui::SameLine();

	static const ImVec2 size_stage = ImGui::GetContentRegionAvail();
	{
		ImGui::BeginChild("stage", size_stage, ImGuiChildFlags_Border);
		if (current_example)
			current_example->on_update(delta);
		else
			on_update_blank_content();
		ImGui::EndChild();
	}

	ImGui::End();
}

void ExampleManager::on_render()
{
	if (!current_example) return;

	current_example->on_render(renderer);
}

ExampleManager::ExampleManager() = default;

ExampleManager::~ExampleManager()
{
	if (current_example)
		current_example->on_exit();

	for (auto& pair : example_pool)
		delete pair.second;
}

void ExampleManager::on_update_subject(const Subject& subject)
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
				switch_to(menu_item.id);
		}
	}
}

void ExampleManager::add_example(Subject& subject, const MenuItem& menu_item, Example* example)
{
	subject.item_list.emplace_back(menu_item);
	example_pool[menu_item.id] = example;
}