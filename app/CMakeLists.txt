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
set(CMAKE_CXX_STANDARD 17)

add_library(Lord_of_the_Seas SHARED
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
        client/ui/views/MovableView.cpp
        common/gamecore/LandingEvent.h
        common/gamecore/PlayerProxy.cpp
        common/gamecore/PlayerProxy.h
        common/gamecore/EdgeOwnerChangedEvent.hpp
        common/gamecore/IGridSquareObserver.hpp
        common/gamecore/IMapBuilderObserver.hpp
        common/gamecore/Position.hpp
        client/ui/ViewBuilder.cpp
        client/ui/ViewBuilder.hpp
        client/ui/views/PlayerView.cpp
        client/ui/views/PlayerView.hpp)

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

add_custom_command(TARGET sfml-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_EXT_DIR}
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    )

foreach(SFML_LIBRARY ${REQUIRED_SFML_LIBRARIES})
    if(NOT ${SFML_LIBRARY} MATCHES "main")
        set(SFML_LIBRARY_FILE_NAME "libsfml-${SFML_LIBRARY}-d.so")
        add_custom_command(TARGET sfml-test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${SFML_DIR}/../../${SFML_LIBRARY_FILE_NAME}
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
            )
    endif(NOT ${SFML_LIBRARY} MATCHES "main")
endforeach(SFML_LIBRARY)
