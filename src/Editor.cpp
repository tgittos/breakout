#include <iostream>
#include "Editor.hpp"
#include "SFMLLevelView.hpp"
#include "Level.hpp"
#include "Dimension.hpp"
#include "SFMLButtonView.hpp"
#include "Button.hpp"
#include "EventManager.hpp"
#include "Clickable.hpp"

void Editor::Start() {
  if(_editorState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Foobar Editor");

  LoadLevel("../test/fixtures/level.txt");
  SFMLLevelView* currentLevelView = new SFMLLevelView(_mainWindow, *_currentLevel);
  _renderables.push_back((SFMLView*)currentLevelView);

  // load UI
  Button* btnExit = new Button("Exit");
  SFMLButtonView* exitButtonView = new SFMLButtonView(_mainWindow, *btnExit);
  _buttons.push_back(btnExit);
  _renderables.push_back((SFMLView*)exitButtonView);

  Button* btnFoobar = new Button("Foobar");
  btnFoobar->GetFeature<Dimension>()->SetY(100);
  SFMLButtonView* foobarButtonView = new SFMLButtonView(_mainWindow, *btnFoobar);
  _buttons.push_back(btnFoobar);
  _renderables.push_back((SFMLView*)foobarButtonView);

  // subscribe to editor events
  EventManager::GetInstance().Subscribe(btnExit->GetEventString(), EventManager::Handler(&ExitHandler));
  EventManager::GetInstance().Subscribe(btnFoobar->GetEventString(), EventManager::Handler(&FoobarHandler));

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
  const sf::Input& input = _mainWindow.GetInput();

  switch(_editorState)
  {
    case Editor::LeftMouseButtonDown:
      if(currentEvent.Type == sf::Event::MouseButtonReleased) {
        _editorState = Editor::Uninitialized;
        // loop through renderables to see what we clicked on
        for(std::list<Button*>::iterator itr = _buttons.begin(); itr != _buttons.end(); ++itr) {
          Button* btn = *itr;
          if (btn->HasFeature<Dimension>()) {
            if(btn->GetFeature<Dimension>()->Inside(input.GetMouseX(), input.GetMouseY()) && btn->HasFeature<Clickable>()) {
              btn->GetFeature<Clickable>()->Click();
            }
          }
        }
      }
      break;
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
      if(currentEvent.Type == sf::Event::MouseButtonPressed &&
         currentEvent.MouseButton.Button == sf::Mouse::Left) {
        _editorState = Editor::LeftMouseButtonDown;
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
std::list<Button*> Editor::_buttons;
Level* Editor::_currentLevel;

void Editor::ExitHandler(void* data) {
  _editorState = Editor::Exiting;
}

void Editor::FoobarHandler(void* data) {
  std::cout << "FOOBAR!" << std::endl;
}
