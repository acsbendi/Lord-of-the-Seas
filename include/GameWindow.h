//
// Created by Bendi on 3/5/2018.
//

#ifndef LORD_OF_THE_SEAS_GAMEWINDOW_H
#define LORD_OF_THE_SEAS_GAMEWINDOW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "IMapObserver.hpp"
#include "Enums.h"

using std::vector;
using sf::RenderWindow;
using sf::Keyboard;
using sf::Event;

class IUserEventObserver;
class IWindowEventObserver;

class GameWindow : public RenderWindow, public IMapObserver {
public:
    static int GRID_SIDE;   ///< The side length of one grid block.
    static int MARGIN;      ///< The margin around the grid structure of the map.

    GameWindow(int width, int height);
    /**
 * @brief Loop for all user input. Waits for the next meaningful event,
 * notifies the appropriate observers, then returns.
 */
    void GetInput();
    /**
 * @brief Notifies the subscribed observers after the window containing the map has been closed.
 */
    void NotifyOnExit() const;
    /**
     * @brief Notifies the subscribed observers after the user has selected a direction.
     */
    void NotifyOnDirectionSelected(Direction) const;
    /**
     * @brief Notifies the subscribed observers whether the user has confirmed the action at hand.
     */
    void NotifyOnConfirmation(bool) const;
    /**
     * @brief Attaches a user event observer from this map.
     * @param observer The user event observer to attach.
     */
    void AttachUserEventObserver(IUserEventObserver *observer);
    /**
     * @brief Detaches a user event observer from this map.
     * @param observer The user event observer to detach.
     */
    void DetachUserEventObserver(IUserEventObserver *observer);
    /**
     * @brief Attaches a window event observer from this map.
     * @param observer The window event observer to attach.
     */
    void AttachWindowEventObserver(IWindowEventObserver *observer);
    /**
     * @brief Detaches a window event observer from this map.
     * @param observer The window event observer to detach.
     */
    void DetachWindowEventObserver(IWindowEventObserver *observer);
    /**
     * @brief Sets whether the window should create its events or not.
     * @param active Should the window create events?
     */
    void SetActive(bool active);
    void Update(Map&) override;

private:
    const int width;
    const int height;
    vector<IUserEventObserver*> userEventObservers; ///< Vector storing the attached user event observers.
    vector<IWindowEventObserver*> windowEventObservers; ///< Vector storing the attached window event observers.
    bool active; ///< Should the window create events?
    bool inputEnd;

    void ClearEventQueue();
    void HandleKeyPress(const Keyboard::Key&);
    void HandleEvent(const Event&);
};


#endif //LORD_OF_THE_SEAS_GAMEWINDOW_H
