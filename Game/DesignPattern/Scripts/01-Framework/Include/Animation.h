#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include <functional>

#include <SDL.h>

#include "Timer.h"
#include "Atlas.h"
#include "Vector2.h"

class Animation
{
private:
	struct Frame
	{
		SDL_Rect rectSrc;
		SDL_Texture* texture = nullptr;

		Frame() = default;
		Frame(SDL_Texture* _texture, const SDL_Rect& _rectSrc): texture(_texture), rectSrc(_rectSrc) {}
		~Frame() = default;
	};

private:
	Vector2 position;
	double angle = 0;
	SDL_FPoint center = { 0 };
	SDL_RendererFlip flipStyle = SDL_FLIP_NONE;

	bool isLoop = true;
	Timer timer;
	std::vector<Frame> frameList;
	size_t frameIdx = 0;
	std::function<void()> onFinished;

public:
	Animation();
	~Animation() = default;
	void SetPosition(const Vector2&);
	void SetRotation(double);
	void SetCenter(const SDL_FPoint&);
	void SetFlip(SDL_RendererFlip);
	void SetLoop(bool);
	void SetInterval(float);
	void SetOnFinished(std::function<void()>);

	void OnUpdate(float);
	void OnRender(SDL_Renderer*) const;

	void Reset();
	void AddFrame(SDL_Texture*, int);
	void AddFrame(Atlas*);

	SDL_Texture* GetCurrentTexture() const;
};

#endif