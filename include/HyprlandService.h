#ifndef HYPRLAND_SERVICE_H
#define HYPRLAND_SERVICE_H

#include <list>
#include "Workspace.h"
#include "Client.h"
#include "WindowRule.h"

class HyprlandService {
  private:
    static std::string configFilePath;
  public:
    static void setConfigFilePath(std::string);
    static std::string getConfigFilePath();
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
    static WindowRule getActiveWorkspaceRule();
};
#endif
