#include "Game.hpp"
void Game::Start(void) {
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Foobar");

  while(!IsExiting())
  {
    GameLoop();
  }

  _mainWindow.Close();
}
bool Game::IsExiting()
{
  if(_gameState == Game::Exiting)
    return true;
  else
    return false;
}
void Game::GameLoop()
{
  sf::Event currentEvent;
  _mainWindow.GetEvent(currentEvent);

  switch(_gameState)
  {
    default:
    {
      if(currentEvent.Type == sf::Event::Closed)
      {
        _gameState = Game::Exiting;
      }
      if(currentEvent.Type == sf::Event::KeyPressed)
      {
        if(sf::Key::Escape == currentEvent.Key.Code)
        {
          _gameState = Game::Exiting;
        }
      }
      _mainWindow.Clear(sf::Color(0,0,0));
      _mainWindow.Display();
    }
  }
}
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
