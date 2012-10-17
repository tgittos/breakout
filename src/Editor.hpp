#ifndef EDITOR_H
#define EDITOR_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Brick.hpp"

class Level;
class SFMLView;

class Editor {
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
    Exiting
  };
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static EditorState _editorState;
  static sf::RenderWindow _mainWindow;
  static std::list<SFMLView*> _renderables;
  static Brick::BrickType _currentType;
  static Level* _currentLevel;

  static bool IsExiting();
  static void EditorLoop();
};

#endif
