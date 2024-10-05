#include <iostream>
#include "Grid.h"
#include "GameCHaracter.h"
#include <SFML/Graphics.hpp>
#include <thread>


int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE), "A* Pathfinding");
    window.setFramerateLimit(30);

    Grid grid(GRID_WIDTH, GRID_HEIGHT);
    GameCharacter character(grid);

    // Trova il percorso da seguire
    std::vector<std::pair<int, int>> path = character.getPath();
    std::size_t path_index = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (path_index < path.size()) {
            character.moveTo(path[path_index]);
            path_index++;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Pause per mostrare il movimento
        }

        window.clear();

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);

                Cell cell = grid.getCell(x, y);
                if (cell == Cell::Wall) {
                    tile.setFillColor(sf::Color::Black);
                } else if (cell == Cell::Free) {
                    tile.setFillColor(sf::Color::White);
                } else if (cell == Cell::Start) {
                    tile.setFillColor(sf::Color::Green);
                } else if (cell == Cell::End) {
                    tile.setFillColor(sf::Color::Red);
                }

                window.draw(tile);
            }
        }

        for (const auto& [trail_x, trail_y] : character.getTrail()) {
            sf::RectangleShape trailShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            trailShape.setFillColor(sf::Color(0, 0, 255, 100));  // Blu traslucido
            trailShape.setPosition(trail_x * TILE_SIZE, trail_y * TILE_SIZE);
            window.draw(trailShape);
        }

        auto [char_x, char_y] = character.getPosition();
        sf::CircleShape characterShape(TILE_SIZE / 2);
        characterShape.setFillColor(sf::Color::Blue);
        characterShape.setPosition(char_x * TILE_SIZE, char_y * TILE_SIZE);

        window.draw(characterShape);

        window.display();
    }

    return 0;
}
