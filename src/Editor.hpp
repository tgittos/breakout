#ifndef EDITOR_H
#define EDITOR_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Brick.hpp"
#include "EventHandler.hpp"

class Level;
class SFMLView;
class Button;

class Editor : public EventHandler {
  public:
  static void Start();

  static void LoadLevel(const char* path);
  static void SaveLevel(const char* path);
  static void NewLevel();

  static void SelectBrickType(Brick::BrickType type);

  static void AddBrick(int x, int y);
  static void RemoveBrick(int x, int y);
  static void ReplaceBrick(int x, int y);

  private:
  enum EditorState {
    Uninitialized,
    LeftMouseButtonDown,
    Exiting
  };
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static EditorState _editorState;
  static sf::RenderWindow _mainWindow;
  static std::list<SFMLView*> _renderables;
  static std::list<Button*> _buttons;
  static Brick::BrickType _currentType;
  static Level* _currentLevel;

  static bool IsExiting();
  static void EditorLoop();

  static void ExitHandler(void* data);
  static void FoobarHandler(void* data);
};

#endif
