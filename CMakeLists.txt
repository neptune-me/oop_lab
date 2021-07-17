cmake_minimum_required(VERSION 3.13)
project(lab8)

set(CMAKE_CXX_STANDARD 17)
add_executable(lab8 main.cpp game/component/Board.cpp game/component/Board.h game/component/User.cpp game/component/User.h factory/Factory.cpp factory/Factory.h game/game.cpp game/game.h game/SingleGame.cpp game/SingleGame.h game/DoubleGame.cpp game/DoubleGame.h game/component/log.h game/component/log.cpp game/component/log.cpp game/component/GameObserver.h game/action/MoveAction.h game/action/MoveAction.cpp game/action/PlayerAction.h game/action/ObtainBonusAction.h game/action/ObtainBonusAction.cpp)