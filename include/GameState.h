//
// Created by Voric and tobisdev on 11/08/2024.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../include/State.h"
#include "../include/Car.h"
#include "../include/Game.h"
#include "../include/ResourceManager.h"

class GameState : public State {
public:
    GameState(Game& game, const std::string& levelFile);
    GameState(Game& game) : car(game.getCar()) {
        initializeCar();
    }

    void handleInput(Game& game) override;
    void loadLevelFromCSV(const std::string &filename, Game &game);

    void update(Game& game) override;
    void render(Game& game) override;

private:
    Car& car;
    float timeSinceLastPrint = 0.0f;

    std::vector<float> rayDistances;
    std::vector<sf::VertexArray> rays;
    std::vector<sf::VertexArray> collisionMarkers;
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::Sprite> placedTiles;
    std::vector<sf::Texture> tiles;

    void debugDrawing(Game& game);
    void initializeCar();
    void performRaycasts(Game& game);
    void initialiazeRays();
    bool isPauseKeyPressed(const sf::Event& event) const;
    sf::RectangleShape createRoad(Game& game) const;
};

#endif // GAMESTATE_H
