//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include "State.h"
#include "Game.h"
#include "ResourceManager.h"
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

class LevelCreator : public State {
public:
    LevelCreator(Game& game);

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    void saveWallToCSV(const std::string& filename);
    void clearDrawing(Game& game);

private:
    void initializeResources(Game& game);
    void createButtons(Game& game);

    void handleExplanationInput(const sf::Event& event);
    void handleTextInput(const sf::Event& event, Game& game);
    void handleMouseInput(const sf::Event& event, Game& game);
    void handleKeyboardInput(const sf::Event& event, Game& game);

    void addTileAtMouse(Game& game);
    void removeTileAtMouse(Game& game);

    void updatePreviewTile(Game& game);

    void drawPlacedTiles(Game& game);
    void drawButtons(Game& game);
    void drawExplanationScreen(Game& game);
    void drawInputBox(Game& game);

    sf::RectangleShape saveButton;
    sf::Text saveButtonText;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    sf::Font font;
    std::vector<sf::Texture> tiles;

    std::vector<sf::Sprite> placedTiles;
    sf::Sprite backgroundSprite;
    std::vector<int> textureIDs;

    int selectedTile = 0;
    bool mouseDown = false;

    sf::Sprite previewTile;
    bool showExplanation = true;

    bool inputActive = false;
    bool rightMouseDown = false;
    std::string inputFileName;
};

#endif // LEVELCREATOR_H
