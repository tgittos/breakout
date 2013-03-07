#ifndef EDITOR_H
#define EDITOR_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Brick.hpp"
#include "EventHandler.hpp"
#include "SFMLLevelView.hpp"

class Level;
class SFMLView;
class Button;

class Editor : public EventHandler {
  public:
  static void Start();

  static void LoadLevel(const char* path);
  static void SaveLevel(const char* path);
  static void NewLevel();

  private:
  enum EditorState {
    Uninitialized,
    LeftMouseButtonDown,
    Exiting
  };
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static EditorState _editorState;
  static Brick::BrickType _currentType;
  static sf::RenderWindow _mainWindow;
  static std::list<SFMLView*> _renderables;
  static std::list<Button*> _buttons;
  static Level* _currentLevel;
  static SFMLLevelView* _currentLevelView;

  static bool IsExiting();
  static void EditorLoop();

  static void ExitHandler(void* data);
  static void DeleteBrickHandler(void* data);
  static void UnbreakableBrickHandler(void* data);
  static void OnePointBrickHandler(void* data);
  static void ThreePointBrickHandler(void* data);
  static void FivePointBrickHandler(void* data);
  static void SevenPointBrickHandler(void* data);
  static void LevelClickHandler(int mouseX, int mouseY);
  static void SaveHandler(void* data);
};

#endif
