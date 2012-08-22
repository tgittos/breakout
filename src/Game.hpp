#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>

class Game
{

public:
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static void Start();

private:
  enum GameState {
    Uninitialized,
    Exiting
  };

  static GameState _gameState;
  static sf::RenderWindow _mainWindow;

  static bool IsExiting();
  static void GameLoop();
};

#endif
