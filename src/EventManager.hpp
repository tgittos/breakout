#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <map>
#include <list>
#include <exception>
#include <string>
#include "EventHandler.hpp"


class EventManager {
  public:
  struct Handler {
    EventHandler* object;
    void (EventHandler::*handlerPointer)(void*);
    void (*staticHandlerPointer)(void*);
    bool isStatic;
  
    Handler(EventHandler* o, void(EventHandler::*h)(void*)):
      object(o), handlerPointer(h), staticHandlerPointer(NULL), isStatic(false) {}
  
    Handler(void(*h)(void*)):
      object(NULL), handlerPointer(NULL), staticHandlerPointer(h), isStatic(true) {}
  };

  static EventManager& GetInstance();

  void Subscribe(const std::string eventIdentifier, Handler handler);

  int SubscriberCount(const std::string eventIdentifier);

  void Dispatch(const std::string eventIdentifier, void* data);

  private:
  EventManager();
  EventManager(EventManager const&); //copy constructor not implemented
  void operator=(EventManager const&); //assignment not implemented

  std::map<const std::string, std::list<Handler>*> _eventSubscriptions;
  std::list<Handler>* GetSubscribers(const std::string eventIdentifier);
};

#endif
