#include "RunningState.h"
#include <sstream>
#include "raylibCpp.h"
engine::RunningState::RunningState(std::shared_ptr<GameData> gameData)
	:
	gameData(std::move(gameData))
{
}

void engine::RunningState::HandleInput()
{
	//Adjust the timer
	if (IsKeyPressed(KEY_UP))
		gameData->timer = std::min(gameData->timer + 0.25f, 5.f);
	if (IsKeyPressed(KEY_DOWN))
		gameData->timer = std::max(gameData->timer - 0.25f, 0.25f);
}

void engine::RunningState::Update(float dt)
{
	accumulator += dt;
	if (accumulator >= gameData->timer)
	{
		if (gameData->robot->IsFinished())
		{
			//TODO : change state to finished
		}
		else
		{
			//Advance the robot
			gameData->robot->Next();
			accumulator = 0.f;
			++moveCounter;
		}
	}
}

void engine::RunningState::Draw()
{
	gameData->board.Draw();
	gameData->robot->DrawRobot();
	gameData->robot->DrawVisitedOutline();
	gameData->robot->DrawTargetedOutline();
	if (gameData->robot->IsFinished())
	{
		if (gameData->robot->HasFoundObjective())
		{
			gameData->robot->DrawFinalObjectivePath();
		}
	}

	//Draw the text
	std::stringstream TimerText, moveCountText, algorithmText;
	//Timer text
	TimerText << "Timer : " << gameData->timer << " secs (Up/Down arrow key to adjust)";
	raycpp::DrawText(TimerText.str(), Vec2<int>{280, 640}, settings::textFontSize / 1.5f, WHITE);
	//Move count text
	moveCountText << "Number of moves : " << moveCounter;
	raycpp::DrawText(moveCountText.str(), Vec2<int>{380, 10}, settings::textFontSize, GREEN);
	//Algorithm text
	algorithmText << "Algorithm : ";
	if (gameData->algorithm == Algorithm::DepthFirst)
		algorithmText << "Depth First Search";
	else
		algorithmText << "Breadth First Search";
	raycpp::DrawText(algorithmText.str(), Vec2<int>{380, 60}, settings::textFontSize / 1.5f, GREEN);
}