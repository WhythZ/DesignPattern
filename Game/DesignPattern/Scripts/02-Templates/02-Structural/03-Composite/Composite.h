#ifndef _COMPOSITE_H_
#define _COMPOSITE_H_

#include <string>
#include <vector>

#include "Vector2.h"
#include "Example.h"

namespace _CompositePattern
{
	class Node
	{
	public:
		using NodeList = std::vector<Node*>;

	protected:
		std::string name;
		Vector2 position;
		Vector2 worldPosition;

		NodeList childList;
		Node* parent = nullptr;

		SDL_Texture* textureIcon = nullptr;

	public:
		Node()
		{
			name = "Node";
			textureIcon = ResourcesManager::Instance()->findTexture("icon-node");
		}

		virtual ~Node()
		{
			for (Node* _child : childList)
				delete _child;
		}

		virtual void OnInspect();
		virtual void OnUpdate(float);
		virtual void OnRender(SDL_Renderer*);

		Node* GetParent() const
		{
			return parent;
		}

		void SetName(const std::string&)
		{
			name = name;
		}

		const std::string& GetName() const
		{
			return name;
		}

		void SetPosition(const Vector2& _position)
		{
			this->position = _position;
		}

		const Vector2& GetPosition() const
		{
			return worldPosition;
		}

		SDL_Texture* GetIcon() const
		{
			return textureIcon;
		}

		void AddChild(Node* _child)
		{
			_child->parent = this;
			childList.push_back(_child);
		}

		void DelChild(Node* _child)
		{
			childList.erase(std::remove(childList.begin(), childList.end(), _child), childList.end());
		}

		NodeList& GetChildList()
		{
			return childList;
		}
	};

	class TextureNode : public Node
	{
	private:
		Vector2 size;
		float rotation = 0;
		int textureIdx = 0;
		SDL_Texture* texture = nullptr;

	public:
		TextureNode() 
		{ 
			name = "TextureNode";
			textureIcon = ResourcesManager::Instance()->findTexture("icon-texture");
		}
		~TextureNode();

		void OnInspect() override;
		void OnRender(SDL_Renderer*) override;

		void SetTexture(SDL_Texture*);

	private:
		void UpdateSize();
	};

	class TextNode : public Node
	{
	private:
		Vector2 size;
		int fontSize = 35;
		bool needUpdate = true;
		std::string text = u8"文本节点";
		SDL_Texture* textureText = nullptr;
		float colorText[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	public:
		TextNode() 
		{ 
			name = "TextNode"; 
			textureIcon = ResourcesManager::Instance()->findTexture("icon-text");
		}
		~TextNode() = default;

		void OnInspect() override;
		void OnRender(SDL_Renderer*) override;

		void SetFontSize(int);
		void SetText(const std::string&);

	private:
		void UpdateTextureText(SDL_Renderer*);
	};

	class AudioNode : public Node
	{
	private:
		int audioIdx = 0;
		std::string audioID;

	public:
		AudioNode()
		{ 
			name = "AudioNode";
			textureIcon = ResourcesManager::Instance()->findTexture("icon-audio");
		}
		~AudioNode() = default;

		void OnInspect() override;

		void SetAudio(Mix_Chunk* audio);
	};
}

class CompositePattern : public Example
{
private:
	bool needShowPopup = false;
	SDL_Texture* textureTarget = nullptr;
	_CompositePattern::Node* worldTree = nullptr;
	_CompositePattern::Node* nodeSelected = nullptr;

public:
	CompositePattern(SDL_Renderer*);
	~CompositePattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;

private:
	void InitWorldTree();
	void RenderTreeView(_CompositePattern::Node*);
	bool RenderMenuItem(SDL_Texture*, const char*);
};

#endif
