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

		MenuItem(const std::string& id, SDL_Texture* icon, const std::string& title): id(id), icon(icon), title(title) {}
	};

	struct Subject
	{
		std::string title;
		std::vector<MenuItem> item_list;
	};

private:
	static ExampleManager* manager;
	SDL_Renderer* renderer = nullptr;

	std::string current_example_id;
	Example* current_example = nullptr;

	SDL_Texture* texture_target = nullptr;
	std::unordered_map<std::string, Example*> example_pool;
	Subject subject_creational, subject_structural, subject_behavioral;

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
