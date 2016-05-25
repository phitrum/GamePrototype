#pragma once
#include "maze.h"
#include "unionFind.h"
#include <utility>


class CompMaze : public Maze
{
private:

	std::vector<std::pair<int, int> > all_edges;
	std::vector<std::pair<int, int> > mst_edges;
	std::vector<std::pair<int, int> > points;
	std::vector<std::vector<char>*> matrix;
	//std::vector<std::vector<char>*> Maze;

	void makeMaze();

	inline int Pos2Idx(int row, int column) {
		return row * WIDTH + column;
	}

	inline std::pair<int, int> Idx2Pos(int idx) {
		int row = idx / WIDTH;
		int column = idx % WIDTH;
		return std::pair<int, int>(row, column);
	}
	// Shuffle a vector
	template <typename T> void ShuffleVector(std::vector<T> *vector) {
		for (int i = 0; i < vector->size(); ++i) {
			std::swap((*vector)[i], (*vector)[rand() % vector->size()]);
		}
	}

	// std::pair < node A, node B >
	void CreateEdges(std::vector<std::pair<int, int> > *edges) {

		for (int row = 1; row < HEIGHT; ++row) {
			for (int column = 1; column < WIDTH; ++column) {
				edges->push_back(std::pair<int, int>(
					Pos2Idx(row, column), Pos2Idx(row, column - 1)));
				edges->push_back(std::pair<int, int>(
					Pos2Idx(row, column), Pos2Idx(row - 1, column)));
			}
		}

		for (int column = 1; column < WIDTH; ++column) {
			edges->push_back(std::pair<int, int>(
				Pos2Idx(0, column), Pos2Idx(0, column - 1)));
		}

		for (int row = 1; row < HEIGHT; ++row) {
			edges->push_back(std::pair<int, int>(
				Pos2Idx(row, 0), Pos2Idx(row - 1, 0)));
		}
	}

	// Convert each edge to the postion in the matrix that must be drawn.
	void ConvertToPaintedPoint(const std::vector<std::pair<int, int> > & edges,
		std::vector<std::pair<int, int> > * painted_points) {
		for (int i = 0; i < edges.size(); ++i) {
			std::pair<int, int> node_a = Idx2Pos(edges[i].first);
			std::pair<int, int> node_b = Idx2Pos(edges[i].second);


			// Convert the vertices positions to their drawn version.
			node_a.first *= 2;
			node_a.second *= 2;
			node_b.first *= 2;
			node_b.second *= 2;

			// Calculate the position of their edge.
			std::pair<int, int> edge;
			edge.first = (node_a.first + node_b.first) / 2;
			edge.second = (node_a.second + node_b.second) / 2;

			painted_points->push_back(edge);
		}

		// Sort the edges to draw them.
		std::sort(painted_points->begin(), painted_points->end());
	}

	void Draw(const std::vector<std::pair<int, int> > & painted_points) {
		int cpp = 0; // cur painted point

		for (int row = 0; row < (HEIGHT * 2) - 1; ++row) {
			for (int column = 0; column < (WIDTH * 2) - 1; ++column) {
				// If it's an vertex position
				if ((row & 1) == 0 && (column & 1) == 0) {
					continue;
				}
				else {
					if (cpp < painted_points.size()
						&& painted_points[cpp].first == row
						&& painted_points[cpp].second == column) {
						matrix.at(row)->at(column) = ' ';
						cpp++;
					}
					else {
						matrix.at(row)->at(column) = 'H';
					}
				}
			}
		}
	}

	void Kruskal(const std::vector<std::pair<int, int> > & all_edges,
		std::vector<std::pair<int, int> > * mst_edges) {
		UnionFind uf;
		uf.Reset(WIDTH * HEIGHT);
		for (int i = 0; i < all_edges.size(); ++i) {
			if (uf.Union(all_edges[i].first, all_edges[i].second)) {
				mst_edges->push_back(all_edges[i]);
			}
		}
	}

public:
	const int WIDTH, HEIGHT;
	void draws(SDL_Renderer* gRenderer);
	CompMaze(const int w, const int h);
};