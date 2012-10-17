#include "Editor.hpp"
#include "SFMLLevelView.hpp"
#include "Level.hpp"
#include "Dimension.hpp"

void Editor::Start() {
  if(_editorState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Foobar Editor");

  //NewLevel();
  LoadLevel("../test/fixtures/level.txt");
  SFMLLevelView* currentLevelView = new SFMLLevelView(_mainWindow, *_currentLevel);
  _renderables.push_back((SFMLView*)currentLevelView);

  while(!IsExiting())
  {
    EditorLoop();
  }

  _mainWindow.Close();
}

bool Editor::IsExiting()
{
  if(_editorState == Editor::Exiting)
    return true;
  else
    return false;
}

void Editor::EditorLoop() {
  sf::Event currentEvent;
  _mainWindow.GetEvent(currentEvent);

  switch(_editorState)
  {
    default:
    {
      if(currentEvent.Type == sf::Event::Closed)
      {
        _editorState = Editor::Exiting;
      }
      if(currentEvent.Type == sf::Event::KeyPressed)
      {
        if(sf::Key::Escape == currentEvent.Key.Code)
        {
          _editorState = Editor::Exiting;
        }
      }
      _mainWindow.Clear(sf::Color::Black);
      for(std::list<SFMLView*>::iterator itr = _renderables.begin(); itr != _renderables.end(); ++itr) {
        (*itr)->Draw();
      }
      _mainWindow.Display();
    }
  }
}

void Editor::NewLevel() {
  _currentLevel = new Level();
}

void Editor::LoadLevel(const char* path) {
  _currentLevel = new Level();
  _currentLevel->LoadFromFile(path);
  // offset the level for testing purposes
  Dimension* d = _currentLevel->GetFeature<Dimension>();
  d->SetX(100);
  d->SetY(50);
}

Editor::EditorState Editor::_editorState = Uninitialized;
sf::RenderWindow Editor::_mainWindow;
std::list<SFMLView*> Editor::_renderables;
Level* Editor::_currentLevel;
