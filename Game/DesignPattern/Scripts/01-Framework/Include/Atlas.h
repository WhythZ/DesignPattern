#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class Atlas
{
private:
	std::vector<SDL_Texture*> texList;

public:
	Atlas() = default;
	~Atlas() = default;

	void Load(const char*, int);
	void Clear();
	void AddTexture(SDL_Texture*);

	SDL_Texture* GetTexture(int) const;
	int GetSize() const;
};

#endif