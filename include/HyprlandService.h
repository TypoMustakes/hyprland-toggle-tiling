#ifndef HYPRLAND_SERVICE_H
#define HYPRLAND_SERVICE_H

#define HYPRLAND_CONF_DIR "~/.config/hypr/"
#define FLOATING_RULE_CONF_FILE HYPRLAND_CONF_DIR "hyprland/floatbydefault.conf"
#define HYPRCTL_BINARY "/usr/bin/hyprctl"
#define NULL_PATH "/dev/null"
#define SET_FLOATING_RULE "/usr/bin/echo 'windowrule = float,class:.*' > " FLOATING_RULE_CONF_FILE
#define REMOVE_FLOATING_RULE "/usr/bin/cat " NULL_PATH " > " FLOATING_RULE_CONF_FILE

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
