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
	if (currentExample)
		currentExample->OnExit();

	for (auto& _pair : examplePool)
		delete _pair.second;
}

void ExampleManager::Init(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
	SDL_SetTextureBlendMode(textureTarget, SDL_BLENDMODE_BLEND);

	subjectCreational.title = u8"һ��������ģʽ";
	SDL_Texture* _textureIconCreational = ResourcesManager::Instance()->findTexture("icon-creational");
	AddExample(subjectCreational, MenuItem("factory_method", _textureIconCreational, u8"01-��������ģʽ"), new FactoryMethodPattern(_renderer));
	AddExample(subjectCreational, MenuItem("abstract_factory", _textureIconCreational, u8"02-���󹤳�ģʽ"), new AbstractFactoryPattern(_renderer));
	AddExample(subjectCreational, MenuItem("builder", _textureIconCreational, u8"03-������ģʽ"), new BuilderPattern(_renderer));
	AddExample(subjectCreational, MenuItem("prototype", _textureIconCreational, u8"04-ԭ��ģʽ"), new PrototypePattern(_renderer));
	AddExample(subjectCreational, MenuItem("singleton", _textureIconCreational, u8"05-����ģʽ"), new SingletonPattern(_renderer));

	subjectStructural.title = u8"�����ṹ��ģʽ";
	SDL_Texture* _textureIconStructural = ResourcesManager::Instance()->findTexture("icon-structural");
	AddExample(subjectStructural, MenuItem("adapter", _textureIconStructural, u8"01-������ģʽ"), new AdapterPattern(_renderer));
	AddExample(subjectStructural, MenuItem("bridge", _textureIconStructural, u8"02-�Ž�ģʽ"), new BridgePattern());
	AddExample(subjectStructural, MenuItem("composite", _textureIconStructural, u8"03-���ģʽ"), new CompositePattern(_renderer));
	AddExample(subjectStructural, MenuItem("decorator", _textureIconStructural, u8"04-װ����ģʽ"), new DecoratorPattern(_renderer));
	AddExample(subjectStructural, MenuItem("facade", _textureIconStructural, u8"05-���ģʽ"), new FacadePattern());
	AddExample(subjectStructural, MenuItem("flyweight", _textureIconStructural, u8"06-��Ԫģʽ"), new FlyweightPattern());
	AddExample(subjectStructural, MenuItem("proxy", _textureIconStructural, u8"07-����ģʽ"), new ProxyPattern(_renderer));

	subjectBehavioral.title = u8"������Ϊģʽ";
	SDL_Texture* _textureIconBehavioral = ResourcesManager::Instance()->findTexture("icon-behavioral");
	AddExample(subjectBehavioral, MenuItem("chain_of_responsibility", _textureIconBehavioral, u8"01-������ģʽ"), new ChainOfResponsibilityPattern());
	AddExample(subjectBehavioral, MenuItem("command", _textureIconBehavioral, u8"02-����ģʽ"), new CommandPattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("iterator", _textureIconBehavioral, u8"03-������ģʽ"), new IteratorPattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("mediator", _textureIconBehavioral, u8"04-�н���ģʽ"), new MediatorPattern());
	AddExample(subjectBehavioral, MenuItem("memento", _textureIconBehavioral, u8"05-����¼ģʽ"), new MementoPattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("observer", _textureIconBehavioral, u8"06-�۲���ģʽ"), new ObserverPattern());
	AddExample(subjectBehavioral, MenuItem("state", _textureIconBehavioral, u8"07-״̬ģʽ"), new StatePattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("strategy", _textureIconBehavioral, u8"08-����ģʽ"), new StrategyPattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("template_method", _textureIconBehavioral, u8"09-ģ�巽��ģʽ"), new TemplateMethodPattern(_renderer));
	AddExample(subjectBehavioral, MenuItem("visitor", _textureIconBehavioral, u8"10-������ģʽ"), new VisitorPattern());
	AddExample(subjectBehavioral, MenuItem("interpreter", _textureIconBehavioral, u8"11-������ģʽ"), new InterpreterPattern(_renderer));
}

void ExampleManager::OnInput(const SDL_Event* _event)
{
	if (!currentExample) return;

	currentExample->OnInput(_event);
}

void ExampleManager::OnUpdate(float _delta)
{
	ImGuiViewport* _viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(_viewport->WorkPos);
	ImGui::SetNextWindowSize(_viewport->WorkSize);
	ImGui::SetNextWindowViewport(_viewport->ID);

	static const ImGuiWindowFlags _flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoSavedSettings;

	ImGui::Begin("main_window", nullptr, _flags);

	static const ImVec2 _menuSize = { 180, ImGui::GetContentRegionAvail().y };
	{
		ImGui::BeginChild("menu", _menuSize, ImGuiChildFlags_Border);
		OnUpdateSubject(subjectCreational);
		OnUpdateSubject(subjectStructural);
		OnUpdateSubject(subjectBehavioral);
		ImGui::EndChild();
	}

	ImGui::SameLine();

	static const ImVec2 _stageSize = ImGui::GetContentRegionAvail();
	{
		ImGui::BeginChild("stage", _stageSize, ImGuiChildFlags_Border);
		if (currentExample)
			currentExample->OnUpdate(_delta);
		else
			OnUpdateBlankContent();
		ImGui::EndChild();
	}

	ImGui::End();
}

void ExampleManager::OnRender()
{
	if (!currentExample) return;

	currentExample->OnRender(renderer);
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
		ImGui::TextDisabled(u8"�����Bilibili~");
		ImGui::EndTooltip();
	}
}

void ExampleManager::OnUpdateSubject(const Subject& _subject)
{
	if (ImGui::CollapsingHeader(_subject.title.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (const MenuItem& _menuItem : _subject.itemList)
		{
			static const ImVec2 _iconSize = 
			{ 
				ImGui::GetTextLineHeightWithSpacing(), 
				ImGui::GetTextLineHeightWithSpacing() 
			};

			ImGui::Image(_menuItem.icon, _iconSize); ImGui::SameLine();
			if (ImGui::Selectable(_menuItem.title.c_str(), currentExampleID == _menuItem.id))
				SwitchTo(_menuItem.id);
		}
	}
}

void ExampleManager::SwitchTo(const std::string& _id)
{
	if (currentExample)
		currentExample->OnExit();

	currentExampleID = _id;
	currentExample = examplePool[_id];

	if (currentExample)
		currentExample->OnEnter();
}

void ExampleManager::AddExample(Subject& _subject, const MenuItem& _menuItem, Example* _example)
{
	_subject.itemList.emplace_back(_menuItem);
	examplePool[_menuItem.id] = _example;
}