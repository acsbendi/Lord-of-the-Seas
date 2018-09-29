//
// Created by Bendi on 3/5/2018.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Context.hpp>
#include "GameWindow.h"
#include "../../common/gamecore/IUserEventObserver.h"
#include "IWindowEventObserver.h"
#include "../../common/gamecore/Map.h"

using std::move;
using std::remove;
using sf::Event;
using sf::Context;
using sf::Keyboard;
using sf::VideoMode;

int GameWindow::GRID_SIDE = 15;
int GameWindow::MARGIN = 15;

GameWindow::GameWindow(const int width, const int height, vector<unique_ptr<GridSquareView>>&& gridSquareViews) : width{width}, height{height}, active{true},
        RenderWindow{VideoMode(static_cast<unsigned>(GRID_SIDE*(width - 1) + 2*MARGIN),
                         static_cast<unsigned>(GRID_SIDE*(height - 1) + 2*MARGIN)),"Lord of the Seas"},
        gridSquareViews{move(gridSquareViews)}{

}

void GameWindow::GetInput() {
    ClearEventQueue();

    Event event{};
    inputEnd = false;
    while (!inputEnd) {
        while (!inputEnd && pollEvent(event)) {
           HandleEvent(event);
        }
    }
}

void GameWindow::ClearEventQueue() {
    Event event{};
    while (pollEvent(event));
}

void GameWindow::HandleEvent(const Event& event) {
    if(active && event.type == Event::KeyPressed){
        HandleKeyPress(event.key.code);
        inputEnd = true;
    } else if(event.type == Event::Closed){
        NotifyOnExit();
        close();
        inputEnd = true;
    } else if (!active){
        inputEnd = true;
    }
}

void GameWindow::HandleKeyPress(const Keyboard::Key& key) {
    switch (key) {
        case Keyboard::Up:
            NotifyOnDirectionSelected(up);
            break;
        case Keyboard::Down:
            NotifyOnDirectionSelected(down);
            break;
        case Keyboard::Right:
            NotifyOnDirectionSelected(right);
            break;
        case Keyboard::Left:
            NotifyOnDirectionSelected(left);
            break;
        case Keyboard::Escape:
            NotifyOnExit();
            break;
        case Keyboard::Return:
            NotifyOnConfirmation(true);
            break;
        default:
            NotifyOnConfirmation(false);
            break;
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

void GameWindow::Show(){
    clear();
    DrawGridSqures();
    DrawMovables();
    display();
}

void GameWindow::DrawGridSqures() {
    for(auto& gridSquareView : gridSquareViews)
        draw(*gridSquareView);
}

void GameWindow::DrawMovables() {
    for(auto& movableView : movableViews)
        draw(*movableView);
}

void GameWindow::Update() {
    Show();
}