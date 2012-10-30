#include "EventManager.hpp"

EventManager& EventManager::GetInstance() {
  static EventManager instance;
  return instance;
}

void EventManager::Subscribe(const std::string eventIdentifier, EventManager::Handler handler) {
  std::list<EventManager::Handler>* subscribers = GetSubscribers(eventIdentifier);
  if (NULL == subscribers) {
    subscribers = new std::list<EventManager::Handler>;
    _eventSubscriptions.insert(std::pair<const std::string, std::list<EventManager::Handler>*>(eventIdentifier, subscribers));
  }
  subscribers->push_back(handler);
}

int EventManager::SubscriberCount(const std::string eventIdentifier) {
  std::map<const std::string, std::list<EventManager::Handler>*>::iterator itr = _eventSubscriptions.find(eventIdentifier);
  if(_eventSubscriptions.end() == itr)
  {
    return 0;
  } else {
    return itr->second->size();
  }
}

std::list<EventManager::Handler>* EventManager::GetSubscribers(const std::string eventIdentifier) {
  std::map<const std::string, std::list<EventManager::Handler>*>::iterator itr = _eventSubscriptions.find(eventIdentifier);
  if(_eventSubscriptions.end() == itr)
  {
    return NULL;
  } else {
    return itr->second;
  }
}

void EventManager::Dispatch(const std::string eventIdentifier, void* data) {
  std::list<EventManager::Handler>* subscribersPtr = GetSubscribers(eventIdentifier);
  if (NULL != subscribersPtr) {
    std::list<EventManager::Handler> subscribers = *subscribersPtr;
    for(std::list<EventManager::Handler>::iterator itr = subscribers.begin(); itr != subscribers.end(); ++itr) {
      EventManager::Handler handler = *itr;
      if (!handler.isStatic) {
        (handler.object->*handler.handlerPointer)(data);
      } else {
        (handler.staticHandlerPointer)(data);
      }
    }
  }
}

EventManager::EventManager() {
  std::map<const std::string, std::list<Handler>*> _eventSubscriptions = std::map<const std::string, std::list<Handler>*>();
}
