#include "EventManager.hpp"

EventManager& EventManager::GetInstance() {
  static EventManager instance;
  return instance;
}

void EventManager::Subscribe(const char* eventIdentifier, EventManager::Handler handler) {
  std::list<EventManager::Handler>* subscribers = GetSubscribers(eventIdentifier);
  if (NULL == subscribers) {
    subscribers = new std::list<EventManager::Handler>;
    _eventSubscriptions.insert(std::pair<const char*, std::list<EventManager::Handler>*>(eventIdentifier, subscribers));
  }
  subscribers->push_back(handler);
}

int EventManager::SubscriberCount(const char* eventIdentifier) {
  std::map<const char*, std::list<EventManager::Handler>*>::iterator itr = _eventSubscriptions.find(eventIdentifier);
  if(_eventSubscriptions.end() == itr)
  {
    return 0;
  } else {
    return itr->second->size();
  }
}

std::list<EventManager::Handler>* EventManager::GetSubscribers(const char* eventIdentifier) {
  std::map<const char*, std::list<EventManager::Handler>*>::iterator itr = _eventSubscriptions.find(eventIdentifier);
  if(_eventSubscriptions.end() == itr)
  {
    return NULL;
  } else {
    return itr->second;
  }
}

void EventManager::Dispatch(const char* eventIdentifier, void* data) {
  std::list<EventManager::Handler>* subscribersPtr = GetSubscribers(eventIdentifier);
  if (NULL != subscribersPtr) {
    std::list<EventManager::Handler> subscribers = *subscribersPtr;
    for(std::list<EventManager::Handler>::iterator itr = subscribers.begin(); itr != subscribers.end(); ++itr) {
      EventManager::Handler handler = *itr;
      (handler.object->*handler.handlerPointer)(data);
    }
  }
}

EventManager::EventManager() {
  std::map<const char*, std::list<Handler>*> _eventSubscriptions = std::map<const char*, std::list<Handler>*>();
}
