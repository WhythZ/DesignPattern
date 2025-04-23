#ifndef _EXAMPLE_MANAGER_H_
#define _EXAMPLE_MANAGER_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "Example.h"

class ExampleManager
{
private:
	struct MenuItem
	{
		std::string id;
		SDL_Texture* icon = nullptr;
		std::string title;

		MenuItem(const std::string& _id, SDL_Texture* _icon, const std::string& _title)
			: id(_id), icon(_icon), title(_title) {}
	};

	struct Subject
	{
		std::string title;
		std::vector<MenuItem> itemList;
	};

private:
	static ExampleManager* manager;
	SDL_Renderer* renderer = nullptr;

	std::string currentExampleID;
	Example* currentExample = nullptr;

	SDL_Texture* textureTarget = nullptr;
	std::unordered_map<std::string, Example*> examplePool;
	Subject subjectCreational, subjectStructural, subjectBehavioral;

public:
	static ExampleManager* Instance();

	void Init(SDL_Renderer*);

	void OnInput(const SDL_Event*);
	void OnUpdate(float);
	void OnRender();

private:
	ExampleManager() = default;
	~ExampleManager();

	void OnUpdateBlankContent();
	void OnUpdateSubject(const Subject&);
	
	void SwitchTo(const std::string&);
	void AddExample(Subject&, const MenuItem&, Example*);
};

#endif
