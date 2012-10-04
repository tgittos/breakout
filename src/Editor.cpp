#include "Editor.hpp"

void Editor::Start() {
  if(_editorState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Foobar Editor");

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
      _mainWindow.Clear(sf::Color(255,255,255));
      _mainWindow.Display();
    }
  }
}

Editor::EditorState Editor::_editorState = Uninitialized;
sf::RenderWindow Editor::_mainWindow;
