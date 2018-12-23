//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_APPLICATION_H
#define LORD_OF_THE_SEAS_APPLICATION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../common/utils/graphics/Button.h"

using std::vector;
using sf::RenderWindow;
using sf::Texture;
using sf::Event;

class Game;

class Application {
public:
    Application();
    void Start();

private:
    static const int WIDTH = 400;
    static const int HEIGHT = 400;
    static const int backgroundTextureToken;
    bool end;
    RenderWindow window;
    vector<Button> buttons;

    void StartNewLocalGame();
    void PlayGameAndShowResults(Game&&);
    void StartNewOnlineGame();
    void StartNewGame(Game&&);
    void HandleEvent(const Event&);
    void HandleKeyPressedEvent(const Event&);
    void NotifyButtonsOnLeftMouseButtonPressed(const Event&);
    void NotifyButtonsOnMouseMoved(const Event&);
    void NotifyButtonsOnEnterPressed() const;
    void HandleMouseMovedEvent(const Event&);
    void HandleClosedEvent(const Event&);
    void DrawElements();
    void DrawBackground();
    void DrawButtons();
    void Exit();
    void ShowScores(int scoreOfPlayer1, int scoreOfPlayer2);
    void Refresh();
};


#endif //LORD_OF_THE_SEAS_APPLICATION_H
