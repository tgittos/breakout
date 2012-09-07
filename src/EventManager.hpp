#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <map>
#include <list>
#include <exception>
#include "ComposableObject.hpp"

class EventManager {
  public:
  struct Handler{
    ComposableObject* object;
    void (ComposableObject::*handlerPointer)(void*);
  
    Handler(ComposableObject* o, void(ComposableObject::*h)(void*)):
      object(o), handlerPointer(h) {}
  };

  static EventManager& GetInstance();

  void Subscribe(const char* eventIdentifier, Handler handler);

  int SubscriberCount(const char* eventIdentifier);

  void Dispatch(const char* eventIdentifier, void* data);

  private:
  EventManager();
  EventManager(EventManager const&); //copy constructor not implemented
  void operator=(EventManager const&); //assignment not implemented

  std::map<const char*, std::list<Handler>*> _eventSubscriptions;
  std::list<Handler>* GetSubscribers(const char*);
};

#endif
