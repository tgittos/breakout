#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "visiblegameobject.hpp"

class GameObjectManager
{
public:
  GameObjectManager();
  ~GameObjectManager();

  void Add(std::string name, VisibleGameObject* gameObject);
  void Remove(std::string name);
  int GetObjectCount() const;
  VisibleGameObject* Get(std::string name) const;

  void UpdateAll();
  void DrawAll(sf::RenderWindow& window);

private:
  std::map<std::string, VisibleGameObject*> _gameObjects;

  struct GameObjectDeallocator
  {
    void operator()(const std::pair<std::string, VisibleGameObject*>& p) const
    {
      delete p.second;
    }
  };
};

#endif
