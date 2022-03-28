#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(int x, int y) {
	xPos = x;
	yPos = y;
	heuristic = 0;
	lowestCost = -1;
	discovered = false;
	parent = nullptr;
}

Vertex::Vertex()
{
	xPos = -1;
	yPos = -1;
	heuristic = 0;
	lowestCost = -1;
	discovered = false;
	parent = nullptr;
}
