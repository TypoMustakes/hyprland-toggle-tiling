#ifndef HYPRLAND_SERVICE_H
#define HYPRLAND_SERVICE_H

#include <list>
#include <string>
#include "Workspace.h"
#include "Client.h"
#include <nlohmann/json.hpp>

class HyprlandService {
 public:
  static Workspace getCurrentWorkspace();
  static std::list<Client> getClients();
  static std::list<Client> getClientsOnActiveWorkspace();
  static void setFloatingRule(bool);
  static void setClientFloating(Client&);
  static void setClientTiled(Client&);
  static void toggleClientFloating(Client&);
  static std::string exec(const std::string& command);
};
#endif
