# CMakeList.txt : CMake project for Warzone, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Warzone")

# Add source to this project's executable.
add_executable (Warzone "Map.cpp" "MapDriver.cpp" "PlayerDriver.cpp" "Orders.cpp" "OrdersDriver.cpp" "Cards.cpp" "CardsDriver.cpp" "GameEngine.cpp" "GameEngineDriver.cpp" "Map.h" "Player.h" "Cards.h" "GameEngine.h" "Orders.h")

# TODO: Add tests and install targets if needed.
