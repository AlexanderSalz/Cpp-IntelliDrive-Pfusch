//
// Created by Voric and Tobias on 11/08/2024.
//

#include "../include/MenuState.h"
#include "CarChooseState.h"
#include "../include/GameState.h"
#include "../include/ResourceManager.h"

MenuState::MenuState()
    : backgroundIndex(1) {

    std::string fontPath = "resources/Rubik-Regular.ttf";
    std::string menuTitlePath = "resources/MenuTitle-Font.ttf";

    if (!loadFont(Textfont, fontPath) || !loadFont(Menufont, menuTitlePath)) {
        return;
    }

    loadBackground();

    sf::Vector2u defaultWindowSize(1920, 1080);
    initializeButton(playButton, Textfont, "Start", defaultWindowSize, 70);
    initializeButton(carButton, Textfont, "Choose your Car", defaultWindowSize, 120);
    initializeButton(levelEditorButton, Textfont, "Level Editor", defaultWindowSize, 170); // Neue Schaltfläche
    initializeButton(systemButton, Textfont, "Settings", defaultWindowSize, 220);
    initializeButton(exitButton, Textfont, "Exit", defaultWindowSize, 270); // Aktualisiere Offset für Exit

    initializeText(changeBgButton, Textfont, "Change Background", 30, 150, defaultWindowSize.y - 30);
    initializeText(title, Menufont, "INTELLIDRIVE", 200, defaultWindowSize.x / 2.0f, defaultWindowSize.y / 4.0f + 100.f);

    initializeText(copyrightText, Textfont,
                   "\u00A9 2024 Devrim Yildiz & Tobias Huber. IntelliDrive is not really a TradeMark of Voric Productions LLC",
                   20, defaultWindowSize.x / 2.0f, defaultWindowSize.y - 50);
    initializeText(versionText, Textfont, "Beta v1.6.0", 20, defaultWindowSize.x - 150, defaultWindowSize.y - 100);
}

void MenuState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        handleMouseInput(game);
    }
}

void MenuState::handleMouseInput(Game& game) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

        if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            game.changeState(std::make_shared<GameState>(game));
        } else if (carButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            game.changeState(std::make_shared<CarChoosingState>());
        } else if (levelEditorButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            game.changeState(std::make_shared<LevelCreator>(game)); // Wechsel zu LevelCreator
        } else if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            game.window.close();
        } else if (changeBgButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            changeBackground();
        }
    }
}

void MenuState::update(Game& game) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

    updateButtonHover(playButton, mousePos);
    updateButtonHover(levelEditorButton, mousePos); // Button Hover-Update hinzufügen
    updateButtonHover(systemButton, mousePos);
    updateButtonHover(carButton, mousePos);
    updateButtonHover(exitButton, mousePos);
}

void MenuState::render(Game& game) {
    game.window.clear();
    game.window.draw(backgroundSprite);
    game.window.draw(title);
    game.window.draw(playButton);
    game.window.draw(levelEditorButton); // Level-Editor-Button rendern
    game.window.draw(systemButton);
    game.window.draw(carButton);
    game.window.draw(exitButton);
    game.window.draw(changeBgButton);
    game.window.draw(copyrightText);
    game.window.draw(versionText);
}

void MenuState::initializeButton(sf::Text& button, const sf::Font& font, const std::string& text, const sf::Vector2u& windowSize, float offsetY) {
    initializeText(button, font, text, 40, static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f + offsetY);
}

void MenuState::initializeText(sf::Text& textItem, const sf::Font& font, const std::string& text, unsigned int size, float x, float y) {
    textItem.setFont(font);
    textItem.setString(text);
    textItem.setCharacterSize(size);
    textItem.setFillColor(sf::Color::White);
    sf::FloatRect bounds = textItem.getLocalBounds();
    textItem.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    textItem.setPosition(x, y);
}

bool MenuState::loadFont(sf::Font& font, const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return false;
    }
    return true;
}

void MenuState::loadBackground() {
    std::string backgroundImagePath = "resources/background" + std::to_string(backgroundIndex) + ".png";
    if (!backgroundTexture.loadFromFile(backgroundImagePath)) {
        std::cerr << "Failed to load background image from path: " << backgroundImagePath << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void MenuState::changeBackground() {
    backgroundIndex = (backgroundIndex % 4) + 1;
    loadBackground();
}

void MenuState::updateButtonHover(sf::Text& button, const sf::Vector2i& mousePos) {
    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        button.setFillColor(sf::Color(255, 215, 0));
        button.setScale(1.1f, 1.1f);
    } else {
        button.setFillColor(sf::Color::White);
        button.setScale(1.0f, 1.0f);
    }
}