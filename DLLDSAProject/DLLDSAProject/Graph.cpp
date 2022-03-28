#include "pch.h"
#include "Graph.h"
#include <cmath>

void Graph::Evaluate(Vertex* vertex, int* adjVertexCount)
{
	// Calculate heuristic (distance from end)
	vertex->heuristic = (int)abs((float)(vertex->xPos - end->xPos)) + (int)abs((float)(vertex->yPos - end->yPos));
	
	// Remove this vertex from the available list
	bool found = false;
	for (int i = 0; i < *adjVertexCount; i++) {
		// If they're at the same address
		if (&adjacentVertices[i] == vertex) {
			found = true;
		}
		// After we found it, we have to slide the following vertices back one to keep the array clean
		else if (found) {
			adjacentVertices[i - 1] = adjacentVertices[i];
		}
	}
	// Adjust the count of the available list
	adjVertexCount--;
	
	// Add available vertices
	// Calculate the lowestCost to adjacent vertices from this vertex
	int adjacentCost = vertex->lowestCost + 10;
	// If the vertex is NOT on the edge
	if (vertex->xPos < width - 1) { // right
		// We know there's a vertex in this direction
		Vertex right = matrix[vertex->xPos + 1][vertex->yPos];

		// If it's not a wall
		if (right.xPos != -1) {
			// If this path is more efficient
			if (adjacentCost < right.lowestCost || right.lowestCost == -1) {
				// Give it the correct lowest cost
				right.lowestCost = adjacentCost;
				// Make it's parent this vertex
				right.parent = vertex;
			}
			
			// If it's not already part of the available list
			if (!right.discovered) {
				adjacentVertices[*adjVertexCount] = right;
				(*adjVertexCount)++;
				right.discovered = true;
			}
		}
	}
	// The rest do the same thing just in different directions
	if (vertex->xPos > 0) { // left
		Vertex left = matrix[vertex->xPos - 1][vertex->yPos];
		if (left.xPos != -1) {
			if (adjacentCost < left.lowestCost || left.lowestCost == -1) {
				left.lowestCost = adjacentCost;
				left.parent = vertex;
			}

			if (!left.discovered) {
				adjacentVertices[*adjVertexCount] = left;
				(*adjVertexCount)++;
				left.discovered = true;
			}
		}
	}
	if (vertex->yPos < height - 1) { // up
		Vertex up = matrix[vertex->xPos][vertex->yPos + 1];
		if (up.xPos != -1) {
			if (adjacentCost < up.lowestCost || up.lowestCost == -1) {
				up.lowestCost = adjacentCost;
				up.parent = vertex;
			}

			if (!up.discovered) {
				adjacentVertices[*adjVertexCount] = up;
				(*adjVertexCount)++;
				up.discovered = true;
			}
		}
	}
	if (vertex->yPos > 0) { // down
		Vertex down = matrix[vertex->xPos][vertex->yPos - 1];
		if (down.xPos != -1) {
			if (adjacentCost < down.lowestCost || down.lowestCost == -1) {
				down.lowestCost = adjacentCost;
				down.parent = vertex;
			}

			if (!down.discovered) {
				adjacentVertices[*adjVertexCount] = down;
				(*adjVertexCount)++;
				down.discovered = true;
			}
		}
	}
}

Graph::Graph(const int** mazeData, int width, int height, int startX, int startY, int endX, int endY)
{
	// Fill the matrix according to the maze data
	// Allocate the first dimension of the array
	matrix = new Vertex*[width];

	for (int x = 0; x < width; x++) {
		// Allocate the second dimension as we move thru the first
		matrix[x] = new Vertex[height];

		for (int y = 0; y < height; y++) {
			// 0 is what we use to denote a tile that can be moved through
			if (mazeData[x][y] == 0) {
				matrix[x][y] = Vertex(x, y);
			}
			else {
				// This is a wall
				matrix[x][y] = Vertex(); // Vertex(-1, -1)
			}
		}
	}

	// Save the width and height
	this->width = width;
	this->height = height;

	// Allocate the available vertices array
	adjacentVertices = new Vertex[width * height];

	// Save the start and end vertices ONLY IF they are valid
	if (startX >= 0 && startX < width && startY >= 0 && startY < height) {
		start = &(matrix[startX][startY]);
	}
	else {
		start = nullptr;
	}
	if (endX >= 0 && endX < width && endY >= 0 && endY < height) {
		end = &(matrix[endX][endY]);
	}
	else {
		end = nullptr;
	}
}

Graph::~Graph()
{
	// Delete the matrix
	for (int i = 0; i < width; i++) {
		// Release the second dimension's arrays
		delete[] matrix[i];
	}
	// Release the first dimension array
	delete[] matrix;

	// Release the available vertices array
	delete[] adjacentVertices;
}

void Graph::SetStart(int x, int y)
{
	start = &matrix[x][y];
}

bool Graph::GetStart(int& x, int& y)
{
	if (start != nullptr) {
		x = start->xPos;
		y = start->yPos;
		return true;
	}
	return false;
}

void Graph::SetEnd(int x, int y)
{
	end = &matrix[x][y];
}

bool Graph::GetEnd(int& x, int& y)
{
	if (end != nullptr) {
		x = end->xPos;
		y = end->yPos;
		return true;
	}
	return false;
}

int** Graph::FindPath(int& pathLength)
{
	// Path
	int** path = (int**)(new int[width * height][2]);

	// Visited vertices
	Vertex* evaluatedVertices = new Vertex[width * height];
	// current evaluated vertex count
	int evalVertexCount = 0;

	// Start the pathfinding at start
	adjacentVertices[0] = *start;
	int adjVertexCount = 1;
	start->lowestCost = 0;
	Vertex* currentVertex = start;
	
	// Loop until the path has the end in it OR there are no more vertices to evaluate
	while (currentVertex != end || adjVertexCount == 0) {

		// Look through available vertices
		currentVertex = &adjacentVertices[0]; // start with the first vertex in the adjacent vertices
		for (int i = 1; i < adjVertexCount; i++) {

			// If its combined score is less than or equal to the previously lowest combined cost
			if (adjacentVertices[i].heuristic + adjacentVertices[i].lowestCost <= currentVertex->heuristic + currentVertex->lowestCost) {

				// If the combined scores are the same AND it has a lesser heuristc score
				if (adjacentVertices[i].heuristic + adjacentVertices[i].lowestCost == currentVertex->heuristic + currentVertex->lowestCost &&
					adjacentVertices[i].heuristic < currentVertex->heuristic) {
					currentVertex = &adjacentVertices[i]; // make this the next vertex to evaluate (at least until we find a better one)
				}
			}
		}

		// Evaluate the selected vertex
		Evaluate(currentVertex, &adjVertexCount);
	}

	// If we found the end
	if (currentVertex == end) {
		// Trace the path thru the vertex parents
		int(*reversePath)[2] = new int[width * height][2];
		int lengthCount = 0;
		while (currentVertex->parent != nullptr) {
			reversePath[lengthCount][0] = currentVertex->xPos;
			reversePath[lengthCount][1] = currentVertex->yPos;
			lengthCount++;
			currentVertex = currentVertex->parent;
		}

		// Copy the positions into the path in the correct (not-reversed) order
		for (int i = 0; i < lengthCount; i++) {
			path[i] = reversePath[lengthCount - i - 1];
		}

		// Set the path length
		pathLength = lengthCount;

		// Release the necessary memory
		delete[] reversePath;
	}
	// If we made it to this point and we haven't found the end, there's no way to get to the end
	else {
		Vertex lowestCost = matrix[0][0];

		// Loop thru the vertices
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				// If it's not a wall AND it's been discovered (at this point that means it's been evaluated)
				if (matrix[i][j].xPos != -1 && matrix[i][j].discovered) {
					// If it has a lower combined cost
					if (matrix[i][j].lowestCost + matrix[i][j].heuristic < lowestCost.lowestCost + lowestCost.heuristic) {
						lowestCost = matrix[i][j];
					}
				}
			}
		}

		// After we found the best destination, we can retrace it's steps
		int(*reversePath)[2] = new int[width * height][2];
		int lengthCount = 0;
		while (currentVertex->parent != nullptr) {
			reversePath[lengthCount][0] = currentVertex->xPos;
			reversePath[lengthCount][1] = currentVertex->yPos;
			lengthCount++;
			currentVertex = currentVertex->parent;
		}

		// Copy the positions into the path in the correct (not-reversed) order
		for (int i = 0; i < lengthCount; i++) {
			path[i] = reversePath[lengthCount - i - 1];
		}

		// Set the path length
		pathLength = lengthCount;

		// Release the necessary memory
		delete[] reversePath;
	}

	return path;
}
