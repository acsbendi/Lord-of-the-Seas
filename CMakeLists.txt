cmake_minimum_required(VERSION 3.9)
project(Lord_of_the_Seas)

set(CMAKE_CXX_STANDARD 17)

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
        src/main.cpp include/IPlayerObserver.h src/GridSquare.cpp include/GridSquare.h include/IUserEventObserver.h include/IWindowEventObserver.h src/Land.cpp include/Land.h src/Treasure.cpp include/Treasure.h src/Water.cpp include/Water.h src/Application.cpp include/Application.h)

include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_ROOT "C:/Program Files/SFML-2.4.2")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()