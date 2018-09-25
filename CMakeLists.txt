cmake_minimum_required(VERSION 3.9)
project(Lord_of_the_Seas)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

add_executable(Lord_of_the_Seas
        include/Army.h
        include/Enums.h
        include/Game.h
        include/GridPoint.h
        include/Map.h
        include/Movable.h
        include/Player.h
        include/Ship.h
        src/Army.cpp
        src/Game.cpp
        src/GridPoint.cpp
        src/Map.cpp
        src/Movable.cpp
        src/Player.cpp
        src/Ship.cpp
        src/main.cpp
        include/IPlayerObserver.h
        src/GridSquare.cpp
        include/GridSquare.h
        include/IUserEventObserver.h
        include/IWindowEventObserver.h
        src/Land.cpp
        include/Land.h
        src/Treasure.cpp
        include/Treasure.h
        src/Water.cpp
        include/Water.h
        src/Application.cpp
        include/Application.h
        src/Button.cpp
        include/Button.h
        src/ScoreDisplay.cpp
        include/ScoreDisplay.h
        include/Graphics.h
        src/OnlineGame.cpp
        include/OnlineGame.h
        src/LocalPlayer.cpp
        include/LocalPlayer.h include/ILocalPlayerObserver.h src/GameWindow.cpp include/GameWindow.h include/IMapObserver.hpp include/Edge.hpp src/MapBuilder.cpp include/MapBuilder.hpp src/GridSquareView.cpp include/GridSquareView.hpp src/WaterView.cpp include/WaterView.hpp src/LandView.cpp include/LandView.hpp src/TreasureView.cpp include/TreasureView.hpp src/ShipView.cpp include/ShipView.hpp src/ArmyView.cpp include/ArmyView.hpp include/MovableView.hpp include/IMovableObserver.hpp src/MovableView.cpp)

add_executable(Lord_of_the_Seas_server src/Server.cpp include/Server.h src/server_main.cpp)

include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_ROOT "C:/Program Files/SFML-2.4.2")

find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(Lord_of_the_Seas_server ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    target_link_libraries(Lord_of_the_Seas ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

