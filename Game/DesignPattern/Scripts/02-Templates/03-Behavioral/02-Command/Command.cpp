﻿#include "Command.h"
#include <imgui.h>

using namespace _CommandPattern;

void Player::OnMove(const SDL_Point& dir)
{
	SDL_Point new_idx = { mapGridIdx.x + dir.x, mapGridIdx.y + dir.y };
	if (new_idx.x < 0 || new_idx.x >= 12 || new_idx.y < 0 || new_idx.y >= 12
		|| map->grids[new_idx.y][new_idx.x] == Map::GridType::Inaccessible)
		return;

	mapGridIdx = new_idx;

	if (!isReplaying)
		cmdList.push_back(new MoveCommand(this, dir));
	
	if (map->grids[new_idx.y][new_idx.x] == Map::GridType::Goal)
	{
		isAchievedGoal = true;
		Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("achieve"), 0);
	}
}

void _CommandPattern::Player::Reset()
{
	cmdIdx = 0;
	mapGridIdx = { 2, 2 };
}

void Player::Replay()
{
	Reset();

	isReplaying = true;
}

CommandPattern::CommandPattern(SDL_Renderer* renderer)
{
	Map::GridType goal = Map::GridType::Goal;
	Map::GridType accs = Map::GridType::Accessible;
	Map::GridType inac = Map::GridType::Inaccessible;

	map.grids =
	{
		{ inac, inac, inac, inac, inac, inac, inac, inac, inac, inac, inac, inac },
		{ inac, accs, accs, accs, accs, inac, inac, inac, inac, inac, inac, inac },
		{ inac, accs, accs, accs, inac, inac, inac, inac, inac, inac, inac, inac },
		{ inac, inac, inac, accs, accs, inac, inac, inac, inac, inac, inac, inac },
		{ inac, accs, inac, accs, accs, accs, accs, accs, accs, accs, accs, inac },
		{ inac, accs, inac, inac, accs, accs, accs, accs, inac, inac, inac, inac },
		{ inac, accs, accs, inac, inac, inac, accs, accs, accs, accs, goal, inac },
		{ inac, accs, accs, accs, accs, inac, accs, accs, accs, accs, accs, inac },
		{ inac, accs, accs, accs, accs, inac, inac, inac, accs, accs, accs, inac },
		{ inac, accs, accs, accs, accs, accs, accs, inac, accs, accs, accs, inac },
		{ inac, accs, accs, accs, accs, accs, accs, inac, accs, accs, accs, inac },
		{ inac, inac, inac, inac, inac, inac, inac, inac, inac, inac, inac, inac },
	};

	player = new Player(&map);

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 576, 576);
}

CommandPattern::~CommandPattern()
{
	delete player;

	SDL_DestroyTexture(textureTarget);
}

void CommandPattern::OnInput(const SDL_Event* event)
{
	player->OnInput(event);
}

void CommandPattern::OnUpdate(float delta)
{
	player->OnUpdate(delta);

	ImGui::BeginDisabled(!player->CanReplay());
	if (ImGui::Button(u8"回放玩家操作", { ImGui::GetContentRegionAvail().x, 35 }))
		player->Replay();
	ImGui::EndDisabled();

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::SetCursorPos({ 15, 15 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用 上/下/左/右 方向键控制角色到达金币处后点击按钮回放玩家操作");
	ImGui::EndChild();
}

void CommandPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 65, 65, 65, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, ResourcesManager::Instance()->FindTexture("maze"), nullptr, nullptr);

	player->OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
