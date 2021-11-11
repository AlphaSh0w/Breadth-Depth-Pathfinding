#pragma once
#include <vector>
#include <stack>
#include "Board.h"
#include "Vec2.h"

enum class NodeState
{
	none,
	visited,
	targeted
};

struct Node
{
	NodeState state = NodeState::none;
	Vec2<int> parent = {-1,-1};
};

//A class that represents a robot that applies the Depth First Search algorithm.
class DFSRobot
{
public:
	DFSRobot(Board& board, Vec2<int> robotPos);//Creates a robot and generates a node graph out of the board.
	bool IsPositionValid(Vec2<int> position) const;//Returns whether or not a position can be moved to (Is not a wall/Is not out of bounds/Hasn't been visited yet/Isn't targeted yet)
	bool IsFinished() const;//Returns true if the robot reached the objective or if it could not find it.
	bool HasFoundObjective() const;//Returns whether or not the robot has found the objective after finishing the algorithm.
	void Next();//Advances the algorithm by one step.
	void DrawRobot() const;//Draws the robot on the board at its current position.
	void DrawVisitedOutline() const;//Outlines the visited cells.
	void DrawTargetedOutline() const;//Outlines the targeted cells.
	void DrawFinalObjectivePath() const;//Outlines the cells to take to reach the objective.
private:
	std::vector<Vec2<int>> CalculateFinalObjectivePath() const;//Traces back the path to the objective once the algorithm is finished.
private:
	std::vector<Node> graph;
	Board& board;
	std::stack<Vec2<int>> positionsStack;
	Vec2<int> currentPos;

	//A vector to hold the path towards the objective once the algorithm is finished
	std::vector<Vec2<int>> finalObjectivePath;
	bool bFoundObjective = false;

	//Initialize direction vectors (will help us reach adjacent cells)
	static constexpr int directionX[] = { 0, 1, 0,-1 };
	static constexpr int directionY[] = {-1, 0, 1, 0 };
};