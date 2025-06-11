#include <nlohmann/json.hpp>
#include "../include/HyprlandService.h"
#include "../include/ShellService.h"
#include "../include/Macros.h"
#include "../include/FileService.h"

using json = nlohmann::json;

Workspace HyprlandService::getCurrentWorkspace() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " activeworkspace -j"));
  return j.get<Workspace>();
};

std::list<Client> HyprlandService::getClients() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " clients -j"));
  return j.get<std::list<Client>>();
};

std::list<Client> HyprlandService::getClientsOnActiveWorkspace() {
  std::list<Client> clients = HyprlandService::getClients();
  int activeWorkspaceID = HyprlandService::getCurrentWorkspace().id;

  for (auto it = clients.begin(); it != clients.end(); ) {
    if (it->workspace.id != activeWorkspaceID) {
      it = clients.erase(it);
    } else {
      ++it;
    }
  }

  return clients;
};

void HyprlandService::setClientFloating(Client& c) {
  ShellService::exec(HYPRCTL_BINARY " dispatch setfloating address:" + c.address);
};

void HyprlandService::setClientTiled(Client& c) {
  ShellService::exec(HYPRCTL_BINARY " dispatch settiled address:" + c.address);
}

void HyprlandService::toggleClientFloating(Client& c) {
  ShellService::exec(HYPRCTL_BINARY " dispatch togglefloating address:" + c.address);
};

void HyprlandService::setFloatingRule(bool b) {
  if (b) {
    FileServices::createOrOverwriteFile(ShellService::getHomePath()+FLOATING_RULE_CONF_FILE, FLOATING_RULE);
  }
  else {
    FileServices::emptyFile(ShellService::getHomePath()+FLOATING_RULE_CONF_FILE);
  }
};

bool HyprlandService::isFloatingRulePresent() {
  return FileServices::doesNonEmptyFileExist(ShellService::getHomePath()+FLOATING_RULE_CONF_FILE);
};