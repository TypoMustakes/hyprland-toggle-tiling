#ifndef HYPRLAND_SERVICE_H
#define HYPRLAND_SERVICE_H

#include <list>
#include "Workspace.h"
#include "Client.h"
#include "WindowRule.h"

class HyprlandService {
  private:
    static std::string configFilePath;
    static std::string getConfigFilePath();

    static std::list<Workspace> getWorkspaces();
    static std::optional<Workspace> getWorkspace(int);
    static Workspace getCurrentWorkspace();

    static std::list<Client> getClients();
    static std::list<Client> getClientsOnActiveWorkspace();
    static Client getActiveClient();

    static bool isFloatingRulePresent(int);
    static bool isFloatingRulePresent(Workspace);
    static std::list<WindowRule> getWindowRules();
    static std::optional<WindowRule> findConflictingRule(WindowRule);
    static void setFloatingRule(bool);
    static void removeRule(WindowRule);

    static void setClientFloating(Client);
    static void setClientTiled(Client);
  public:
    static void toggleFloating();
    static void moveToWorkspace(int);
    static void setConfigFilePath(std::string);
    static WindowRule getActiveWorkspaceRule();
};
#endif
