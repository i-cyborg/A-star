//
// Created by volta on 05/10/2024.
//

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

class GameCharacter {
public:
    GameCharacter(const Grid& grid) : grid(grid) {
        position = grid.getStart();
    }

    std::vector<std::pair<int, int>> findPath() {
        using P = std::pair<int, int>;
        auto [end_x, end_y] = grid.getEnd();

        auto heuristic = [&](P a, P b) {
            return std::abs(a.first - b.first) + std::abs(a.second - b.second);
        };

        std::priority_queue<std::pair<int, P>, std::vector<std::pair<int, P>>, std::greater<>> frontier;
        frontier.push({0, position});

        std::map<P, P> came_from;
        std::map<P, int> cost_so_far;
        came_from[position] = position;
        cost_so_far[position] = 0;

        std::vector<P> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!frontier.empty()) {
            P current = frontier.top().second;
            frontier.pop();

            if (current == P{end_x, end_y}) {
                break;
            }

            for (auto [dx, dy] : directions) {
                int next_x = current.first + dx;
                int next_y = current.second + dy;
                P next{next_x, next_y};

                if (next_x < 0 || next_x >= grid.getWidth() || next_y < 0 || next_y >= grid.getHeight()) {
                    continue;
                }
                if (grid.getCell(next_x, next_y) == Cell::Wall) {
                    continue;
                }

                int new_cost = cost_so_far[current] + 1;
                if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    int priority = new_cost + heuristic({end_x, end_y}, next);
                    frontier.push({priority, next});
                    came_from[next] = current;
                }
            }
        }

        std::vector<P> path;
        for (P current = {end_x, end_y}; current != position; current = came_from[current]) {
            path.push_back(current);
        }
        path.push_back(position);
        std::reverse(path.begin(), path.end());
        return path;
    }

    std::vector<std::pair<int, int>> getPath() {
        return findPath();
    }

    void moveTo(const std::pair<int, int>& newPosition) {
        position = newPosition;
        trail.push_back(newPosition);
    }

    std::pair<int, int> getPosition() const {
        return position;
    }

    const std::vector<std::pair<int, int>>& getTrail() const {
        return trail;
    }

private:
    std::pair<int, int> position;
    std::vector<std::pair<int, int>> trail;
    const Grid& grid;
};



#endif //GAMECHARACTER_H
