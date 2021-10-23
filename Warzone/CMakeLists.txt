# CMakeList.txt : CMake project for Warzone, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
#set (CMAKE_CXX_STANDARD 11)

project ("Warzone")

# Add source to this project's executable.
add_executable (Warzone "Map.cpp" "Drivers/MapDriver.cpp" "Drivers/PlayerDriver.cpp" "Player.cpp" "Orders.cpp" "Drivers/OrdersDriver.cpp" "Cards.cpp" "Drivers/CardsDriver.cpp" "GameEngine.cpp" "Drivers/GameEngineDriver.cpp" "Headers/Map.h" "Headers/Player.h" "Headers/Cards.h" "Headers/GameEngine.h" "Headers/Orders.h"  "Headers/MapDriver.h")

# TODO: Add tests and install targets if needed.
