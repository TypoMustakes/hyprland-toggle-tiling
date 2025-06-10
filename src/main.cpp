#include "../include/HyprlandService.h"

int main(int, char**){
  for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
    HyprlandService::setClientFloating(c);
  }
  HyprlandService::setFloatingRule(true);

  sleep(5);

  for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
    HyprlandService::setClientTiled(c);
  }
  HyprlandService::setFloatingRule(false);
}