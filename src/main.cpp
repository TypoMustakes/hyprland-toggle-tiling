#include "../include/HyprlandService.h"

int main(int, char**){
  if (HyprlandService::isFloatingRulePresent()) {
    for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
      HyprlandService::setClientTiled(c);
    }
    HyprlandService::setFloatingRule(false);
  } else {
    for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
      HyprlandService::setClientFloating(c);
    }
    HyprlandService::setFloatingRule(true);
  }
}