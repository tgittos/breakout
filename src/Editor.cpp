#include <iostream>
#include <fstream>
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

  std::ifstream file("data/level");
  if (file.good())
  {
    LoadLevel("data/level");
  }
  else
  {
    NewLevel();
  }
  _currentLevelView = new SFMLLevelView(_mainWindow, *_currentLevel);
  _renderables.push_back((SFMLView*)_currentLevelView);

  // load UI
  Button* btnExit = new Button("Exit");
  SFMLButtonView* exitButtonView = new SFMLButtonView(_mainWindow, *btnExit);
  _buttons.push_back(btnExit);
  _renderables.push_back((SFMLView*)exitButtonView);
  // wire up events
  EventManager::GetInstance().Subscribe(btnExit->GetEventString(), EventManager::Handler(&ExitHandler));
  
  // set up model
  Button* btnDeleteBrick = new Button("Delete Brick");
  btnDeleteBrick->GetFeature<Dimension>()->SetY(100);
  btnDeleteBrick->GetFeature<Dimension>()->SetWidth(200);
  // set up view
  SFMLButtonView* deleteBrickButtonView = new SFMLButtonView(_mainWindow, *btnDeleteBrick);
  _buttons.push_back(btnDeleteBrick);
  _renderables.push_back((SFMLView*)deleteBrickButtonView);
  EventManager::GetInstance().Subscribe(btnDeleteBrick->GetEventString(), EventManager::Handler(&DeleteBrickHandler));
  
  Button* btnUnbreakableBrick = new Button("Unbreakable");
  btnUnbreakableBrick->GetFeature<Dimension>()->SetY(150);
  btnUnbreakableBrick->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* unbreakableBrickButtonView = new SFMLButtonView(_mainWindow, *btnUnbreakableBrick);
  _buttons.push_back(btnUnbreakableBrick);
  _renderables.push_back((SFMLView*)unbreakableBrickButtonView);
  EventManager::GetInstance().Subscribe(btnUnbreakableBrick->GetEventString(),EventManager::Handler(&UnbreakableBrickHandler));
  
  Button* btnOnePointBrick = new Button("1 Point");
  btnOnePointBrick->GetFeature<Dimension>()->SetY(200);
  btnOnePointBrick->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* onePointBrickView = new SFMLButtonView(_mainWindow, *btnOnePointBrick);
  _buttons.push_back(btnOnePointBrick);
  _renderables.push_back((SFMLView*)onePointBrickView);
  EventManager::GetInstance().Subscribe(btnOnePointBrick->GetEventString(),EventManager::Handler(&OnePointBrickHandler));
  
  Button* btnThreePointBrick = new Button("3 Points");
  btnThreePointBrick->GetFeature<Dimension>()->SetY(250);
  btnThreePointBrick->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* threePointBrickView = new SFMLButtonView(_mainWindow, *btnThreePointBrick);
  _buttons.push_back(btnThreePointBrick);
  _renderables.push_back((SFMLView*)threePointBrickView);
  EventManager::GetInstance().Subscribe(btnThreePointBrick->GetEventString(),EventManager::Handler(&ThreePointBrickHandler));
  
  Button* btnFivePointBrick = new Button("5 Points");
  btnFivePointBrick->GetFeature<Dimension>()->SetY(300);
  btnFivePointBrick->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* fivePointBrickView = new SFMLButtonView(_mainWindow, *btnFivePointBrick);
  _buttons.push_back(btnFivePointBrick);
  _renderables.push_back((SFMLView*)fivePointBrickView);
  EventManager::GetInstance().Subscribe(btnFivePointBrick->GetEventString(),EventManager::Handler(&FivePointBrickHandler));
  
  Button* btnSevenPointBrick = new Button("7 Points");
  btnSevenPointBrick->GetFeature<Dimension>()->SetY(350);
  btnSevenPointBrick->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* sevenPointBrickView = new SFMLButtonView(_mainWindow, *btnSevenPointBrick);
  _buttons.push_back(btnSevenPointBrick);
  _renderables.push_back((SFMLView*)sevenPointBrickView);
  EventManager::GetInstance().Subscribe(btnSevenPointBrick->GetEventString(),EventManager::Handler(&SevenPointBrickHandler));
  
  Button* btnSave = new Button("Save");
  btnSave->GetFeature<Dimension>()->SetY(450);
  btnSave->GetFeature<Dimension>()->SetWidth(200);
  SFMLButtonView* saveView = new SFMLButtonView(_mainWindow, *btnSave);
  _buttons.push_back(btnSave);
  _renderables.push_back((SFMLView*)saveView);
  EventManager::GetInstance().Subscribe(btnSave->GetEventString(), EventManager::Handler(&SaveHandler));

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
              break;
            }
          }
        }
        // probably wasn't a button, lets see if it was a renderable

      }
      // see if we clicked on the level
      // this is outside the if statement so we can support
      // mouse dragging
      if (_currentLevel->GetFeature<Dimension>()->Inside(input.GetMouseX(), input.GetMouseY())) {
        LevelClickHandler(input.GetMouseX(), input.GetMouseY());
        break;
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
    }
  }
  _mainWindow.Clear(sf::Color::White);
  for(std::list<SFMLView*>::iterator itr = _renderables.begin(); itr != _renderables.end(); ++itr) {
    (*itr)->Draw();
  }
  _mainWindow.Display();
}

void Editor::NewLevel() {
  _currentLevel = new Level();
  Dimension* d = _currentLevel->GetFeature<Dimension>();
  d->SetX(200);
  d->SetY(50);
}

void Editor::LoadLevel(const char* path) {
  _currentLevel = new Level();
  _currentLevel->LoadFromFile(path);
  // offset the level for testing purposes
  Dimension* d = _currentLevel->GetFeature<Dimension>();
  d->SetX(200);
  d->SetY(50);
}

Editor::EditorState Editor::_editorState = Uninitialized;
sf::RenderWindow Editor::_mainWindow;
std::list<SFMLView*> Editor::_renderables;
std::list<Button*> Editor::_buttons;
Level* Editor::_currentLevel;
SFMLLevelView* Editor::_currentLevelView;
Brick::BrickType Editor::_currentType;

void Editor::ExitHandler(void* data) {
  _editorState = Editor::Exiting;
}

void Editor::DeleteBrickHandler(void* data) {
  std::cout << "setting type to empty" << std::endl;
  _currentType = Brick::EMPTY;
}

void Editor::UnbreakableBrickHandler(void* data) {
  std::cout << "setting type to unbreakable" << std::endl;
  _currentType = Brick::UNBREAKABLE;
}

void Editor::OnePointBrickHandler(void* data) {
  std::cout << "setting type to 1 point" << std::endl;
  _currentType = Brick::ONE_POINT;
}

void Editor::ThreePointBrickHandler(void* data) {
  std::cout << "setting type to 3 points" << std::endl;
  _currentType = Brick::THREE_POINTS;
}

void Editor::FivePointBrickHandler(void* data) {
  std::cout << "setting type to 5 points" << std::endl;
  _currentType = Brick::FIVE_POINTS;
}

void Editor::SevenPointBrickHandler(void* data) {
  std::cout << "setting type to 7 points" << std::endl;
  _currentType = Brick::SEVEN_POINTS;
}

void Editor::LevelClickHandler(int mouseX, int mouseY) {
  // convert mouse x/y to brick index
  int* coords = _currentLevelView->MapMouseToBrick(mouseX, mouseY);
  _currentLevel->ChangeBrick(coords[0], coords[1], _currentType);
  delete coords;
}

void Editor::SaveHandler(void* data) {
  _currentLevel->SaveToFile("data/level");
  std::cout << "saved" << std::endl;
}
