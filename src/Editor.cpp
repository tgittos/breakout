#include <iostream>
#include "Editor.hpp"
#include "SFMLLevelView.hpp"
#include "Level.hpp"
#include "Dimension.hpp"
#include "SFMLButtonView.hpp"
#include "Button.hpp"
#include "EventManager.hpp"

void Editor::Start() {
  if(_editorState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Foobar Editor");

  LoadLevel("../test/fixtures/level.txt");
  SFMLLevelView* currentLevelView = new SFMLLevelView(_mainWindow, *_currentLevel);
  _renderables.push_back((SFMLView*)currentLevelView);

  // load UI
  Button* b = new Button("Exit");
  SFMLButtonView* exitButtonView = new SFMLButtonView(_mainWindow, *b);
  _renderables.push_back((SFMLView*)exitButtonView);

  // subscribe to editor events
  EventManager::GetInstance().Subscribe(b->GetEventString(), EventManager::Handler(&ExitHandler));

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
      if(currentEvent.Type == sf::Event::MouseButtonReleased &&
         currentEvent.MouseButton.Button == sf::Mouse::Left) {
        // loop through renderables to see what we clicked on
        for(std::list<SFMLView*>::iterator itr = _renderables.begin(); itr != _renderables.end(); ++itr) {
          SFMLView* view = *itr;
          if (NULL != dynamic_cast<SFMLButtonView*>(view)) {
            (dynamic_cast<SFMLButtonView*>(view))->Click();
          }
          /*
          if (view->HasFeature<Dimension>()) {
            if(view->GetFeature<Dimension>()->Inside(input.GetMouseX(), input.GetMouseY()) && view->HasFeature<Clickable>()) {
              view->GetFeature<Clickable>->Click();
            }
          }
          */
        }
      }
      _mainWindow.Clear(sf::Color::White);
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

void Editor::ExitHandler(void* data) {
  _editorState = Editor::Exiting;
}
