#include "Animation.h"

Animation::Animation()
{
	timer.SetOneShot(false);
	timer.SetOnTimeout(
		[&]()
		{
			frameIdx++;
			if (frameIdx >= frameList.size())
			{
				frameIdx = isLoop ? 0 : frameList.size() - 1;
				if (!isLoop && onFinished)
					onFinished();
			}
		}
	);
}

void Animation::SetPosition(const Vector2& position)
{
	this->position = position;
}

void Animation::SetRotation(double angle)
{
	this->angle = angle;
}

void Animation::SetCenter(const SDL_FPoint& center)
{
	this->center = center;
}

void Animation::SetFlip(SDL_RendererFlip flip)
{
	flipStyle = flip;
}

void Animation::SetLoop(bool isLoop)
{
	this->isLoop = isLoop;
}

void Animation::SetInterval(float interval)
{
	timer.SetWaitTime(interval);
}

void Animation::SetOnFinished(std::function<void()> onFinished)
{
	this->onFinished = onFinished;
}

void Animation::OnUpdate(float delta)
{
	timer.OnUpdate(delta);
}

void Animation::OnRender(SDL_Renderer* renderer) const
{
	const Frame& frame = frameList[frameIdx];

	SDL_FRect rect_dst;
	rect_dst.x = position.x - frame.rectSrc.w / 2;
	rect_dst.y = position.y - frame.rectSrc.h / 2;
	rect_dst.w = (float)frame.rectSrc.w, rect_dst.h = (float)frame.rectSrc.h;

	SDL_RenderCopyExF(renderer, frame.texture, &frame.rectSrc, &rect_dst, angle, &center, flipStyle);
}

void Animation::Reset()
{
	timer.Restart();

	frameIdx = 0;
}

void Animation::AddFrame(SDL_Texture* texture, int numH)
{
	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	int width_frame = width / numH;

	for (int i = 0; i < numH; i++)
	{
		SDL_Rect rectSrc;
		rectSrc.x = i * width_frame, rectSrc.y = 0;
		rectSrc.w = width_frame, rectSrc.h = height;

		frameList.emplace_back(texture, rectSrc);
	}
}

void Animation::AddFrame(Atlas* atlas)
{
	for (int i = 0; i < atlas->GetSize(); i++)
	{
		SDL_Texture* texture = atlas->GetTexture(i);

		int width, height;
		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

		SDL_Rect rectSrc;
		rectSrc.x = 0, rectSrc.y = 0;
		rectSrc.w = width, rectSrc.h = height;

		frameList.emplace_back(texture, rectSrc);
	}
}

SDL_Texture* Animation::GetCurrentTexture() const
{
	return frameList[frameIdx].texture;
}
