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

void Animation::SetPosition(const Vector2& _position)
{
	this->position = _position;
}

void Animation::SetRotation(double _angle)
{
	this->angle = _angle;
}

void Animation::SetCenter(const SDL_FPoint& _center)
{
	this->center = _center;
}

void Animation::SetFlip(SDL_RendererFlip _flip)
{
	flipStyle = _flip;
}

void Animation::SetLoop(bool _isLoop)
{
	this->isLoop = _isLoop;
}

void Animation::SetInterval(float _interval)
{
	timer.SetWaitTime(_interval);
}

void Animation::SetOnFinished(std::function<void()> _onFinished)
{
	this->onFinished = _onFinished;
}

void Animation::OnUpdate(float _delta)
{
	timer.OnUpdate(_delta);
}

void Animation::OnRender(SDL_Renderer* _renderer) const
{
	const Frame& _frame = frameList[frameIdx];

	SDL_FRect rectDst;
	rectDst.x = position.x - _frame.rectSrc.w / 2;
	rectDst.y = position.y - _frame.rectSrc.h / 2;
	rectDst.w = (float)_frame.rectSrc.w, rectDst.h = (float)_frame.rectSrc.h;

	SDL_RenderCopyExF(_renderer, _frame.texture, &_frame.rectSrc, &rectDst, angle, &center, flipStyle);
}

void Animation::Reset()
{
	timer.Restart();
	frameIdx = 0;
}

void Animation::AddFrame(SDL_Texture* _texture, int _numH)
{
	int _width, _height;
	SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height);

	int _widthFrame = _width / _numH;

	for (int i = 0; i < _numH; i++)
	{
		SDL_Rect _rectSrc;
		_rectSrc.x = i * _widthFrame, _rectSrc.y = 0;
		_rectSrc.w = _widthFrame, _rectSrc.h = _height;

		frameList.emplace_back(_texture, _rectSrc);
	}
}

void Animation::AddFrame(Atlas* _atlas)
{
	for (int i = 0; i < _atlas->GetSize(); i++)
	{
		SDL_Texture* _texture = _atlas->GetTexture(i);

		int _width, _height;
		SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height);

		SDL_Rect _rectSrc;
		_rectSrc.x = 0, _rectSrc.y = 0;
		_rectSrc.w = _width, _rectSrc.h = _height;

		frameList.emplace_back(_texture, _rectSrc);
	}
}

SDL_Texture* Animation::GetCurrentTexture() const
{
	return frameList[frameIdx].texture;
}
