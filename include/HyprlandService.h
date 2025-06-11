#ifndef HYPRLAND_SERVICE_H
#define HYPRLAND_SERVICE_H

#include <list>
#include "Workspace.h"
#include "Client.h"
#include "WindowRule.h"

class HyprlandService {
 public:
  static Workspace getCurrentWorkspace();
  static std::list<Client> getClients();
  static std::list<Client> getClientsOnActiveWorkspace();
  static std::list<WindowRule> getWindowRules();
  static std::optional<WindowRule> findConflictingRule(WindowRule);
  static void setFloatingRule(bool);
  static void removeRule(WindowRule);
  static void setClientFloating(Client&);
  static void setClientTiled(Client&);
  static void toggleClientFloating(Client&);
  static bool isFloatingRulePresent();
};
#endif
