#pragma once
#include "Vertex.h"

class Graph
{
	Vertex** matrix; // holds the maze data (Vertex(-1, -1) for walls)
	int width;
	int height;
	Vertex** adjacentVertices; // Vertices available for evaluating
	Vertex* start;
	Vertex* end;

	void Evaluate(Vertex* vertex, int& adjVertexCount);
	int CalcHeuristic(Vertex* vertex);

public:
	Graph(const int** mazeData, int width, int height, int startX, int startY, int endX, int endY);
	~Graph();

	void SetStart(int x, int y);
	bool GetStart(int& x, int& y);
	void SetEnd(int x, int y);
	bool GetEnd(int& x, int& y);
	int** FindPath(int& pathLength);
};

