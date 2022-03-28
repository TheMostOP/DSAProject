#pragma once
struct Vertex
{
	// Fields
	int xPos;
	int yPos;
	int heuristic;
	int lowestCost;
	bool discovered;
	Vertex* parent;

	// Constructor
	Vertex(int x, int y);
	Vertex();
};

