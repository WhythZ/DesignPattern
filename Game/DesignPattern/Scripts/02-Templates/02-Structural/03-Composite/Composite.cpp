#include "Composite.h"

#include <imgui.h>
#include <imgui_stdlib.h>

using namespace _CompositePattern;

static bool ComboGetter(void* _data, int _n, const char** _outStr)
{
	ResourcesManager::ResIDList* id_list = (ResourcesManager::ResIDList*)_data;
	*_outStr = (*id_list)[_n].c_str();

	return true;
}

void Node::OnInspect()
{
	ImGui::TextDisabled(u8"空节点");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75);

	ImGui::TextUnformatted(u8"名称："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::InputText(u8"##名称", &name);
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"位置："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::DragFloat2(u8"##位置", &position.x, 0.1f, 0, 0, "%.2f");
	ImGui::NextColumn();

	ImGui::Columns(1);
}

void _CompositePattern::Node::OnUpdate(float _delta)
{
	if (GetParent())
		worldPosition = GetParent()->GetPosition() + position;

	for (Node* _child : childList)
		_child->OnUpdate(_delta);
}

void _CompositePattern::Node::OnRender(SDL_Renderer* _renderer)
{
	for (Node* _child : childList)
		_child->OnRender(_renderer);
}

_CompositePattern::TextureNode::~TextureNode()
{
	SDL_DestroyTexture(texture);
}

void TextureNode::OnInspect()
{
	Node::OnInspect();

	ImGui::Separator();

	ImGui::TextDisabled(u8"纹理节点");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75);

	ImGui::TextUnformatted(u8"纹理："); ImGui::NextColumn(); 
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	const ResourcesManager::ResIDList& _residList = ResourcesManager::Instance()->getTextureResIDList();
	if (ImGui::Combo("##纹理", &textureIdx, &ComboGetter, (void*)(&_residList), (int)_residList.size()))
	{
		texture = ResourcesManager::Instance()->findTexture(_residList[textureIdx]);
		UpdateSize();
	}
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"尺寸："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::DragFloat2(u8"##尺寸", &size.x, 1.0f, 0.0f, FLT_MAX, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"旋转："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::DragFloat(u8"##旋转", &rotation, 0.1f, 0, 0, "%.2f deg");
	ImGui::NextColumn();

	ImGui::Columns(1);
}

void TextureNode::OnRender(SDL_Renderer* _renderer)
{
	SDL_FRect _rect = { worldPosition.x, worldPosition.y, size.x, size.y };
	SDL_RenderCopyExF(_renderer, texture, nullptr, &_rect, rotation, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);

	Node::OnRender(_renderer);
}

void TextureNode::SetTexture(SDL_Texture* _texture)
{
	texture = _texture;

	const ResourcesManager::ResIDList& _residList = ResourcesManager::Instance()->getTextureResIDList();
	for (int i = 0; i < _residList.size(); i++)
	{
		if (_texture == ResourcesManager::Instance()->findTexture(_residList[i]))
		{
			textureIdx = i;
			break;
		}
	}

	UpdateSize();
}

void TextureNode::UpdateSize()
{
	int _w, _h;
	SDL_QueryTexture(texture, nullptr, nullptr, &_w, &_h);
	size = { (float)_w, (float)_h };
}

void TextNode::OnInspect()
{
	Node::OnInspect();

	ImGui::Separator();

	ImGui::TextDisabled(u8"文本节点");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75);

	ImGui::TextUnformatted(u8"文本："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	if (ImGui::InputText(u8"##文本", &text))
		needUpdate = true;
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"颜色："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	if (ImGui::ColorEdit4(u8"##颜色", colorText, ImGuiColorEditFlags_AlphaPreview))
		needUpdate = true;
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"字号："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	if (ImGui::DragInt(u8"##字号", &fontSize, 1.0f, 10, 500, "%d px", ImGuiSliderFlags_AlwaysClamp))
		needUpdate = true;
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"尺寸："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::DragFloat2(u8"##尺寸", &size.x, 1.0f, 0.0f, FLT_MAX, "%.2f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::NextColumn();

	ImGui::Columns(1);
}

void TextNode::OnRender(SDL_Renderer* _renderer)
{
	if (needUpdate)
	{
		UpdateTextureText(_renderer);
		needUpdate = false;
	}

	SDL_FRect rect = { worldPosition.x, worldPosition.y, size.x, size.y };
	SDL_RenderCopyF(_renderer, textureText, nullptr, &rect);

	Node::OnRender(_renderer);
}

void _CompositePattern::TextNode::SetFontSize(int _fontSize)
{
	this->fontSize = _fontSize;
	needUpdate = true;
}

void TextNode::SetText(const std::string& _text)
{
	text = _text;
	needUpdate = true;
}

void TextNode::UpdateTextureText(SDL_Renderer* _renderer)
{
	SDL_DestroyTexture(textureText); textureText = nullptr;

	SDL_Color _color =
	{
		(Uint8)(colorText[0] * 255), (Uint8)(colorText[1] * 255),
		(Uint8)(colorText[2] * 255), (Uint8)(colorText[3] * 255)
	};
	SDL_Surface* _surface = TTF_RenderUTF8_Blended(ResourcesManager::Instance()
		->findFont("SarasaMonoSC-Regular")->GetFont(fontSize), text.c_str(), _color);
	if (!_surface) { size = { 0, 0 }; return; }

	textureText = SDL_CreateTextureFromSurface(_renderer, _surface);
	size = { (float)_surface->w, (float)_surface->h };
	SDL_FreeSurface(_surface);
}

void AudioNode::OnInspect()
{
	Node::OnInspect();

	ImGui::Separator();

	ImGui::TextDisabled(u8"音频节点");

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 75);

	ImGui::TextUnformatted(u8"音频："); ImGui::NextColumn();
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	const ResourcesManager::ResIDList& _residList = ResourcesManager::Instance()->getAudioResIDList();
	ImGui::Combo("##音频", &audioIdx, &ComboGetter, (void*)(&_residList), (int)_residList.size());
	ImGui::NextColumn();

	ImGui::TextUnformatted(u8"播放："); ImGui::NextColumn();
	static const ImVec2 _btnSize = { ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight() };
	if (ImGui::ImageButton(ResourcesManager::Instance()->findTexture("icon-play"), _btnSize))
		Mix_PlayChannel(-1, ResourcesManager::Instance()->findAudio(ResourcesManager::Instance()->getAudioResIDList()[audioIdx]), 0);
	ImGui::NextColumn();

	ImGui::Columns(1);
}

void _CompositePattern::AudioNode::SetAudio(Mix_Chunk* audio)
{
	const ResourcesManager::ResIDList& _residList = ResourcesManager::Instance()->getAudioResIDList();
	for (int _i = 0; _i < _residList.size(); _i++)
	{
		if (audio == ResourcesManager::Instance()->findAudio(_residList[_i]))
		{
			audioIdx = _i;
			break;
		}
	}
}

CompositePattern::CompositePattern(SDL_Renderer* _renderer)
{
	InitWorldTree();

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 470, 450);
}

CompositePattern::~CompositePattern()
{
	delete worldTree;
	SDL_DestroyTexture(textureTarget);
}

void CompositePattern::OnUpdate(float _delta)
{
	worldTree->OnUpdate(_delta);

	{
		ImGui::BeginChild("tree_view", { 250, ImGui::GetContentRegionAvail().y }, 
			ImGuiChildFlags_Border, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
		RenderTreeView(worldTree);
		ImGui::EndChild();
	}

	ImGui::SameLine();
	{
		ImGui::BeginGroup();
		{
			ImGui::BeginChild("scene_view", { ImGui::GetContentRegionAvail().x, 455 }, ImGuiChildFlags_Border);
			ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
			ImGui::EndChild();
		}
		{
			ImGui::BeginChild("inspector", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Border);
			if (nodeSelected) nodeSelected->OnInspect();
			ImGui::EndChild();
		}
		ImGui::EndGroup();
	}

	if (needShowPopup)
	{
		ImGui::OpenPopup("context menu");
		needShowPopup = false;
	}

	if (ImGui::BeginPopup("context menu"))
	{
		if (ImGui::BeginMenu(u8"添加节点"))
		{
			if (RenderMenuItem(ResourcesManager::Instance()->findTexture("icon-node"), u8"空节点"))
				nodeSelected->AddChild(new Node());
			if (RenderMenuItem(ResourcesManager::Instance()->findTexture("icon-texture"), u8"纹理节点"))
				nodeSelected->AddChild(new TextureNode());
			if (RenderMenuItem(ResourcesManager::Instance()->findTexture("icon-text"), u8"文本节点"))
				nodeSelected->AddChild(new TextNode());
			if (RenderMenuItem(ResourcesManager::Instance()->findTexture("icon-audio"), u8"音频节点"))
				nodeSelected->AddChild(new AudioNode());
			ImGui::EndMenu();
		}

		ImGui::BeginDisabled(nodeSelected && !nodeSelected->GetParent());
		if (ImGui::MenuItem(u8"删除节点"))
		{
			if (nodeSelected && nodeSelected->GetParent())
			{
				nodeSelected->GetParent()->DelChild(nodeSelected);
				delete nodeSelected; nodeSelected = nullptr;
			}
		}
		ImGui::EndDisabled();

		ImGui::EndPopup();
	}
}

void CompositePattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 65, 65, 65, 255);
	SDL_RenderClear(_renderer);

	worldTree->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}

void CompositePattern::InitWorldTree()
{
	worldTree = new Node();
	worldTree->SetName(u8"世界树");
	{
		AudioNode* _nodeAudio = new AudioNode();
		_nodeAudio->SetName(u8"背景音乐");
		_nodeAudio->SetAudio(ResourcesManager::Instance()->findAudio("bgm"));
		worldTree->AddChild(_nodeAudio);
	}
	{
		Node* _nodeBrave = new Node();
		_nodeBrave->SetName(u8"勇者");
		_nodeBrave->SetPosition({ 75, 125 });
		{
			TextureNode* _nodeTexture = new TextureNode();
			_nodeTexture->SetName(u8"动画静帧");
			_nodeTexture->SetTexture(ResourcesManager::Instance()->findTexture("brave"));
			_nodeBrave->AddChild(_nodeTexture);

			TextNode* _nodeText = new TextNode();
			_nodeText->SetName(u8"你的名字");
			_nodeText->SetPosition({ -10, 155 });
			_nodeText->SetFontSize(20);
			_nodeText->SetText(u8"- 芝士勇者 -");
			_nodeBrave->AddChild(_nodeText);

			AudioNode* _nodeAudio = new AudioNode();
			_nodeAudio->SetName(u8"私人笑声");
			_nodeAudio->SetAudio(ResourcesManager::Instance()->findAudio("manbo"));
			_nodeBrave->AddChild(_nodeAudio);
		}
		worldTree->AddChild(_nodeBrave);
	}
	{
		Node* _nodeIceSword = new Node();
		_nodeIceSword->SetName(u8"寒冰大剑");
		_nodeIceSword->SetPosition({ 300, 120 });
		{
			TextureNode* _nodeTexture = new TextureNode();
			_nodeTexture->SetName(u8"冰剑");
			_nodeTexture->SetTexture(ResourcesManager::Instance()->findTexture("BlueSword"));
			_nodeIceSword->AddChild(_nodeTexture);

			TextNode* _nodeText = new TextNode();
			_nodeText->SetName(u8"剑名");
			_nodeText->SetPosition({ -40, 65 });
			_nodeText->SetFontSize(15);
			_nodeText->SetText(u8"稀有 寒冰大剑");
			_nodeIceSword->AddChild(_nodeText);
		}
		worldTree->AddChild(_nodeIceSword);
	}
	{
		Node* _nodeIceSword = new Node();
		_nodeIceSword->SetName(u8"雷火剑");
		_nodeIceSword->SetPosition({ 300, 220 });
		{
			TextureNode* _nodeTexture = new TextureNode();
			_nodeTexture->SetName(u8"火剑");
			_nodeTexture->SetTexture(ResourcesManager::Instance()->findTexture("RedSword"));
			_nodeIceSword->AddChild(_nodeTexture);

			TextNode* _nodeText = new TextNode();
			_nodeText->SetName(u8"剑名");
			_nodeText->SetPosition({ -30, 65 });
			_nodeText->SetFontSize(15);
			_nodeText->SetText(u8"罕见 雷火剑");
			_nodeIceSword->AddChild(_nodeText);
		}
		worldTree->AddChild(_nodeIceSword);
	}
}

void CompositePattern::RenderTreeView(Node* _node)
{
	static const ImVec2 _iconSize = { ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight() };
	static const ImGuiTreeNodeFlags _baseFlag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnDoubleClick;

	bool _isOpen = false;
	bool _hasChild = !_node->GetChildList().empty();

	if (!_hasChild)
	{
		ImGui::TreeNodeEx((void*)_node->GetName().c_str(), _baseFlag
			| ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
			((nodeSelected == _node) ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None), "");
	}
	else
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		_isOpen = ImGui::TreeNodeEx((void*)_node->GetName().c_str(), _baseFlag |
			((nodeSelected == _node) ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_None), "");
	}

	if (ImGui::IsItemClicked(ImGuiMouseButton_Left) || ImGui::IsItemClicked(ImGuiMouseButton_Right))
		nodeSelected = _node;

	if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		needShowPopup = true;

	ImGui::SameLine();
	ImGui::Image(_node->GetIcon(), _iconSize);
	ImGui::SameLine();
	ImGui::TextUnformatted(_node->GetName().c_str());

	if (_hasChild && _isOpen)
	{
		for (Node* _child : _node->GetChildList())
			RenderTreeView(_child);

		ImGui::TreePop();
	}
}

bool CompositePattern::RenderMenuItem(SDL_Texture* _texture, const char* _text)
{
	static const ImVec2 _iconSize = { ImGui::GetTextLineHeight(), ImGui::GetTextLineHeight() };

	ImGui::Image(_texture, _iconSize);
	ImGui::SameLine();
	return ImGui::MenuItem(_text);
}
