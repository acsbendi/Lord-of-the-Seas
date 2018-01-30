//
// Created by Bendi on 1/28/2018.
//

#ifndef LORD_OF_THE_SEAS_APPLICATION_H
#define LORD_OF_THE_SEAS_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <functional>

class Application {
private:
    class Button : public sf::Drawable{
    private:
        const std::function<void()> action;
        const std::string text;
        const sf::IntRect rect; ///< The coordinates and dimensions of the button's rectangle's top-left corner.
        static const sf::Font font;
        static const sf::Texture texture;
    public:
        Button(int x, int y, int width, int height, std::string text, std::function<void()> action);

        void draw(sf::RenderTarget &target, sf::RenderStates) const override;
        void onClick(int x, int y) const;
        static const sf::Font createFont(std::string fileName);
    };

    static const int WIDTH = 400;
    static const int HEIGHT = 400;
    static const sf::Texture background;
    bool end;
    sf::RenderWindow window;
    std::vector<Button> buttons;

    void startNewLocalGame() const;
    void startNewOnlineGame() const;
    void exit();
    void showScores(int scoreOfPlayer1,int scoreOfPlayer2) const;
    void refresh();
    static const sf::Texture createTexture(const std::string& fileName);

public:
    Application();
    void start();
};


#endif //LORD_OF_THE_SEAS_APPLICATION_H
