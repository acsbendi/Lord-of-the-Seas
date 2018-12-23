cmake_minimum_required(VERSION 3.4.1)
project(Lord_of_the_Seas)

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(REQUIRED_SFML_LIBRARIES graphics network window system audio main activity)

set(SFML_DIR "${ANDROID_NDK}/sources/third_party/sfml/lib/${ANDROID_ABI}/cmake/SFML")
find_package(SFML COMPONENTS ${REQUIRED_SFML_LIBRARIES} REQUIRED)

set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_STANDARD 14)

set(CPP_SOURCES_PREFIX src/main/cpp)

add_library(Lord_of_the_Seas SHARED
        ${CPP_SOURCES_PREFIX}/common/gamecore/Army.h
        ${CPP_SOURCES_PREFIX}/common/utils/Enums.h
        ${CPP_SOURCES_PREFIX}/client/games/Game.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/GridPoint.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Map.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Movable.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Player.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Ship.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Army.cpp
        ${CPP_SOURCES_PREFIX}/client/games/Game.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/GridPoint.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Map.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Movable.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Player.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Ship.cpp
        ${CPP_SOURCES_PREFIX}/client/main.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/IPlayerObserver.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/GridSquare.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/GridSquare.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/IUserEventObserver.h
        ${CPP_SOURCES_PREFIX}/client/ui/IWindowEventObserver.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Land.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Land.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Treasure.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Treasure.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/Water.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Water.h
        ${CPP_SOURCES_PREFIX}/client/application/Application.cpp
        ${CPP_SOURCES_PREFIX}/client/application/Application.h
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/Button.cpp
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/Button.h
        ${CPP_SOURCES_PREFIX}/client/ui/ScoreDisplay.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/ScoreDisplay.h
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/ResourceManager.cpp
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/ResourceManager.hpp
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/ResourceNotFoundException.cpp
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/ResourceNotFoundException.hpp
        ${CPP_SOURCES_PREFIX}/common/utils/graphics/Graphics.h
        ${CPP_SOURCES_PREFIX}/client/games/OnlineGame.cpp
        ${CPP_SOURCES_PREFIX}/client/games/OnlineGame.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/LocalPlayer.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/LocalPlayer.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/ILocalPlayerObserver.h
        ${CPP_SOURCES_PREFIX}/client/ui/GameWindow.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/GameWindow.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/IMapObserver.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/Edge.hpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/MapBuilder.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/MapBuilder.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/GridSquareView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/GridSquareView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/WaterView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/WaterView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/LandView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/LandView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/TreasureView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/TreasureView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/ShipView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/ShipView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/ArmyView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/ArmyView.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/MovableView.hpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/IMovableObserver.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/MovableView.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/LandingEvent.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/PlayerProxy.cpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/PlayerProxy.h
        ${CPP_SOURCES_PREFIX}/common/gamecore/EdgeOwnerChangedEvent.hpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/IGridSquareObserver.hpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/IMapBuilderObserver.hpp
        ${CPP_SOURCES_PREFIX}/common/gamecore/Position.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/ViewBuilder.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/ViewBuilder.hpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/PlayerView.cpp
        ${CPP_SOURCES_PREFIX}/client/ui/views/PlayerView.hpp)

if(SFML_FOUND)
    foreach(SFML_LIBRARY ${REQUIRED_SFML_LIBRARIES})
        set(SFML_LIBRARY_FULL_NAME "sfml-${SFML_LIBRARY}")
        target_link_libraries(Lord_of_the_Seas ${SFML_LIBRARY_FULL_NAME})
    endforeach(SFML_LIBRARY)
endif()

# add lib dependencies
target_link_libraries(Lord_of_the_Seas
    android
    EGL
    GLESv1_CM
    log)

set(SFML_EXT_DIR "${ANDROID_NDK}/sources/third_party/sfml/extlibs/lib/${ANDROID_ABI}")

add_custom_command(TARGET Lord_of_the_Seas POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_EXT_DIR}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    )

foreach(SFML_LIBRARY ${REQUIRED_SFML_LIBRARIES})
    if(NOT ${SFML_LIBRARY} MATCHES "main")
        set(SFML_LIBRARY_FILE_NAME "libsfml-${SFML_LIBRARY}-d.so")
        add_custom_command(TARGET Lord_of_the_Seas POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_DIR}/../../${SFML_LIBRARY_FILE_NAME}
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
            )
    endif(NOT ${SFML_LIBRARY} MATCHES "main")
endforeach(SFML_LIBRARY)
