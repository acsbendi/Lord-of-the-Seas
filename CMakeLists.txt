cmake_minimum_required(VERSION 3.9)
project(Lord_of_the_Seas)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

add_executable(Lord_of_the_Seas
        common/gamecore/Army.h
        common/utils/Enums.h
        client/games/Game.h
        common/gamecore/GridPoint.h
        common/gamecore/Map.h
        common/gamecore/Movable.h
        common/gamecore/Player.h
        common/gamecore/Ship.h
        common/gamecore/Army.cpp
        client/games/Game.cpp
        common/gamecore/GridPoint.cpp
        common/gamecore/Map.cpp
        common/gamecore/Movable.cpp
        common/gamecore/Player.cpp
        common/gamecore/Ship.cpp
        client/main.cpp
        common/gamecore/IPlayerObserver.h
        common/gamecore/GridSquare.cpp
        common/gamecore/GridSquare.h
        common/gamecore/IUserEventObserver.h
        client/ui/IWindowEventObserver.h
        common/gamecore/Land.cpp
        common/gamecore/Land.h
        common/gamecore/Treasure.cpp
        common/gamecore/Treasure.h
        common/gamecore/Water.cpp
        common/gamecore/Water.h
        client/application/Application.cpp
        client/application/Application.h
        common/utils/graphics/Button.cpp
        common/utils/graphics/Button.h
        client/ui/ScoreDisplay.cpp
        client/ui/ScoreDisplay.h
        common/utils/graphics/Graphics.h
        client/games/OnlineGame.cpp
        client/games/OnlineGame.h
        common/gamecore/LocalPlayer.cpp
        common/gamecore/LocalPlayer.h
        common/gamecore/ILocalPlayerObserver.h
        client/ui/GameWindow.cpp
        client/ui/GameWindow.h
        common/gamecore/IMapObserver.hpp
        client/ui/Edge.hpp
        common/gamecore/MapBuilder.cpp
        common/gamecore/MapBuilder.hpp
        client/ui/views/GridSquareView.cpp
        client/ui/views/GridSquareView.hpp
        client/ui/views/WaterView.cpp
        client/ui/views/WaterView.hpp
        client/ui/views/LandView.cpp
        client/ui/views/LandView.hpp
        client/ui/views/TreasureView.cpp
        client/ui/views/TreasureView.hpp
        client/ui/views/ShipView.cpp
        client/ui/views/ShipView.hpp
        client/ui/views/ArmyView.cpp
        client/ui/views/ArmyView.hpp
        client/ui/views/MovableView.hpp
        common/gamecore/IMovableObserver.hpp
        client/ui/views/MovableView.cpp common/gamecore/LandingEvent.h common/gamecore/PlayerProxy.cpp common/gamecore/PlayerProxy.h common/gamecore/EdgeOwnerChangedEvent.hpp common/gamecore/IGridSquareObserver.hpp common/gamecore/IMapBuilderObserver.hpp common/gamecore/Position.hpp client/ui/ViewBuilder.cpp client/ui/ViewBuilder.hpp client/ui/views/PlayerView.cpp client/ui/views/PlayerView.hpp)

add_executable(Lord_of_the_Seas_server server/Server.cpp server/Server.h server/server_main.cpp)

set(SFML_ROOT "C:/Program Files/SFML-2.4.2")

find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(Lord_of_the_Seas_server ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(Lord_of_the_Seas ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

