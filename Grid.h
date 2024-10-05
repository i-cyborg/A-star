//
// Created by volta on 05/10/2024.
//

#ifndef GRID_H
#define GRID_H



#include <vector>
#include <stack>
#include <random>
#include <algorithm>

const int GRID_WIDTH = 31; // Deve essere dispari per creare un labirinto
const int GRID_HEIGHT = 31;
const int TILE_SIZE = 32;

enum class Cell {
    Wall,
    Free,
    Start,
    End
};

class Grid {
public:
    Grid(int width, int height) : width(width), height(height) {
        generateMaze();
    }

    void generateMaze() {
        grid.resize(height, std::vector<Cell>(width, Cell::Wall));

        std::random_device rd;
        std::mt19937 gen(rd());

        auto is_valid_position = [&](int x, int y) {
            return x > 0 && x < width - 1 && y > 0 && y < height - 1 && grid[y][x] == Cell::Wall;
        };

        std::stack<std::pair<int, int>> stack;
        int start_x = std::uniform_int_distribution<>(1, (width - 1) / 2)(gen) * 2 + 1;
        int start_y = std::uniform_int_distribution<>(1, (height - 1) / 2)(gen) * 2 + 1;
        stack.push({start_x, start_y});

        grid[start_y][start_x] = Cell::Free;

        std::vector<std::pair<int, int>> directions = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};

        while (!stack.empty()) {
            auto [x, y] = stack.top();
            std::shuffle(directions.begin(), directions.end(), gen);

            bool moved = false;
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (is_valid_position(nx, ny)) {
                    grid[ny][nx] = Cell::Free;
                    grid[y + dy / 2][x + dx / 2] = Cell::Free;
                    stack.push({nx, ny});
                    moved = true;
                    break;
                }
            }

            if (!moved) {
                stack.pop();
            }
        }

        start = {1, 1};
        end = {width - 2, height - 2};
        grid[start.second][start.first] = Cell::Start;
        grid[end.second][end.first] = Cell::End;
    }

    Cell getCell(int x, int y) const {
        return grid[y][x];
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    std::pair<int, int> getStart() const {
        return start;
    }

    std::pair<int, int> getEnd() const {
        return end;
    }

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> grid;
    std::pair<int, int> start;
    std::pair<int, int> end;
};



#endif //GRID_H
