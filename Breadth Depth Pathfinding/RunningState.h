#pragma once
#include "State.h"
#include "Game.h"
#include <memory>

namespace engine
{
	class RunningState : public State
	{
	public:
		RunningState(std::shared_ptr<GameData> in_gameData);
		void HandleInput() override;
		void Update(float dt) override;
		void Draw() override;
	private:
		std::shared_ptr<GameData> gameData;
		float accumulator = 0.f;
	};
}
