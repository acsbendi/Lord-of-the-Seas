//
// Created by Bendi on 3/5/2018.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Context.hpp>
#include "GameWindow.h"
#include "IUserEventObserver.h"
#include "IWindowEventObserver.h"
#include "Map.h"

using std::remove;
using sf::Event;
using sf::Context;
using sf::Keyboard;
using sf::VideoMode;

int GameWindow::GRID_SIDE = 15;
int GameWindow::MARGIN = 15;

GameWindow::GameWindow(const int width, const int height) : width{width}, height{height}, active{true},
        RenderWindow{VideoMode(static_cast<unsigned>(GRID_SIDE*(width - 1) + 2*MARGIN),
                         static_cast<unsigned>(GRID_SIDE*(height - 1) + 2*MARGIN)),"Lord of the Seas"} {

}

void GameWindow::GetInput() {
    Event event{};
    Context context{};


    //clearing event queue
    while (pollEvent(event));

    while (true) {
        while (pollEvent(event)) {
            if (active && event.type == Event::KeyPressed){
                switch (event.key.code) {
                    case Keyboard::Up:
                        NotifyOnDirectionSelected(up);
                        return;
                    case Keyboard::Down:
                        NotifyOnDirectionSelected(down);
                        return;
                    case Keyboard::Right:
                        NotifyOnDirectionSelected(right);
                        return;
                    case Keyboard::Left:
                        NotifyOnDirectionSelected(left);
                        return;
                    case Keyboard::Escape:
                        NotifyOnExit();
                        return;
                    case Keyboard::Return:
                        NotifyOnConfirmation(true);
                        return;
                    default:
                        NotifyOnConfirmation(false);
                        return;
                }
            }
            else if (event.type == Event::Closed) {
                NotifyOnExit();
                close();
                return;
            } else if (!active)
                return;
        }
    }
}

void GameWindow::NotifyOnExit() const {
    for(auto observer : windowEventObservers)
        observer->OnExit();
}

void GameWindow::NotifyOnConfirmation(bool confirmed) const {
    for(auto observer : userEventObservers)
        observer->OnConfirmation(confirmed);
}

void GameWindow::NotifyOnDirectionSelected(Direction direction) const {
    for(auto observer : userEventObservers)
        observer->OnDirectionSelected(direction);
}

void GameWindow::AttachUserEventObserver(IUserEventObserver *observer){
    userEventObservers.push_back(observer);
}

void GameWindow::DetachUserEventObserver(IUserEventObserver *observer){
    userEventObservers.erase(remove(userEventObservers.begin(),
                                         userEventObservers.end(),observer),userEventObservers.end());
}

void GameWindow::AttachWindowEventObserver(IWindowEventObserver *observer){
    windowEventObservers.push_back(observer);
}

void GameWindow::DetachWindowEventObserver(IWindowEventObserver *observer){
    windowEventObservers.erase(remove(windowEventObservers.begin(),
                                           windowEventObservers.end(),observer),windowEventObservers.end());
}

void GameWindow::SetActive(bool active) {
    this->active = active;
}

void GameWindow::Update(Map& map) {
    map.Show(*this);
}