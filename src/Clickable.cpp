#include "Clickable.hpp"
#include "EventManager.hpp"

Clickable::Clickable(std::string ns):
  _namespace(ns) {
}

void Clickable::Click() {
  EventManager::GetInstance().Dispatch(GetEventString(), NULL);
}

std::string Clickable::GetEventString() {
  return _namespace + std::string("::") + CLICK;
}

const std::string Clickable::CLICK("click");
