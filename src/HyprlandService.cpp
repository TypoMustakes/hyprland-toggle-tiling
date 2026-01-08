#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include "../include/HyprlandService.h"
#include "../include/ShellService.h"
#include "../include/Macros.h"
#include "../include/FileService.h"

using json = nlohmann::json;

std::string HyprlandService::configFilePath;

void HyprlandService::setConfigFilePath(std::string path) {
  //Look for substring "~/". If found, expand it
  const std::string tilde = "~/";
  size_t pos = path.find(tilde);
  if (pos != std::string::npos) {
    path.replace(pos, tilde.length(), ShellService::getHomePath());
  }
  configFilePath = path;
};

std::string HyprlandService::getConfigFilePath() {
  return configFilePath;
};

std::list<Workspace> HyprlandService::getWorkspaces() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " workspaces -j"));
  return j.get<std::list<Workspace>>();
}

std::optional<Workspace> HyprlandService::getWorkspace(int id) {
  std::list<Workspace> workspaces = getWorkspaces();
  
  for (auto it = workspaces.begin(); it != workspaces.end(); ) {
    if (it->id == id) {
	  return *it;
    } else {
      ++it;
    }
  }

  return std::nullopt;
}

Workspace HyprlandService::getCurrentWorkspace() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " activeworkspace -j"));
  return j.get<Workspace>();
};

Client HyprlandService::getActiveClient() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " activewindow -j"));
  return j.get<Client>();
}

std::list<Client> HyprlandService::getClients() {
  json j = json::parse(ShellService::exec(HYPRCTL_BINARY " clients -j"));
  return j.get<std::list<Client>>();
};

std::list<Client> HyprlandService::getClientsOnActiveWorkspace() {
  std::list<Client> clients = getClients();
  int activeWorkspaceID = getCurrentWorkspace().id;

  for (auto it = clients.begin(); it != clients.end(); ) {
    if (it->workspace.id != activeWorkspaceID) {
      it = clients.erase(it);
    } else {
      ++it;
    }
  }

  return clients;
};

std::list<WindowRule> HyprlandService::getWindowRules() {
  std::list<WindowRule> rules;

  for (auto& line : FileService::readLines(getConfigFilePath())) {
    rules.push_back(WindowRule::parse(line));
  }

  return rules;
};

void HyprlandService::setClientFloating(Client c) {
  ShellService::exec(HYPRCTL_BINARY " dispatch setfloating address:" + c.address);
};

void HyprlandService::setClientTiled(Client c) {
  ShellService::exec(HYPRCTL_BINARY " dispatch settiled address:" + c.address);
}

//on = true -> creates a window rule to ENABLE floating mode for currently active workspace
//on = false -> creates a window rule to DISABLE floating mode for currently active workspace
void HyprlandService::setFloatingRule(bool on) {
  WindowRule rule {.tile = !on, .workspaceID = getCurrentWorkspace().id};
  auto conflictingRule = findConflictingRule(rule);
  if (conflictingRule.has_value()) {
    removeRule(conflictingRule.value());
  }

  FileService::appendToFile(
    getConfigFilePath(),
    rule.toString()
  );
};

std::optional<WindowRule> HyprlandService::findConflictingRule(WindowRule subject) {
  std::list<WindowRule> rules = getWindowRules();
  int id = getCurrentWorkspace().id;

  for (auto& rule : rules) {
    if (rule.tile == !subject.tile && rule.workspaceID == subject.workspaceID)
    {
      return rule;
    }
  }

  return std::nullopt;
};

void HyprlandService::removeRule(WindowRule rule) {
  std::list<WindowRule> rules = getWindowRules();
  int index = 0;
  int foundIndex = -1;

  for (auto& it : rules) {
    if (it.toString() == rule.toString())
    {
      foundIndex = index;
      break;
    }
    ++index;
  }

  if (foundIndex != -1) {
    FileService::deleteNthLine(
      getConfigFilePath(),
      foundIndex
    );
  }

  //else: rule not found, do nothing
}

bool HyprlandService::isFloatingRulePresent(int workspaceId) {
  std::list<WindowRule> rules = getWindowRules();

  for (auto& rule : rules) {
    if (rule.workspaceID == workspaceId && rule.tile == false) {
      return true;
    }
  }

  return false;
}

bool HyprlandService::isFloatingRulePresent(Workspace workspace) {
  return isFloatingRulePresent(workspace.id);
};

WindowRule HyprlandService::getActiveWorkspaceRule() {
  std::list<WindowRule> rules = getWindowRules();
  int id = getCurrentWorkspace().id;

  for (auto& rule : rules) {
    if (rule.workspaceID == id) {
      return rule;
    }
  }

  //If no rule is found, return a default rule (tiled)
  return WindowRule {.tile = true, .workspaceID = id};
};

void HyprlandService::moveToWorkspace(int workspaceId) {
  if (isFloatingRulePresent(workspaceId)) {
	setClientFloating(getActiveClient());
  } else {
	setClientTiled(getActiveClient());
  }
  
  ShellService::exec(HYPRCTL_BINARY " dispatch movetoworkspace " + std::to_string(workspaceId));
}

void HyprlandService::toggleFloating() {
  if (isFloatingRulePresent(getCurrentWorkspace())) {
    for (auto& c : getClientsOnActiveWorkspace()) {
	  setClientTiled(c);
    }
    setFloatingRule(false);
  } else {
    for (auto& c : getClientsOnActiveWorkspace()) {
	  setClientFloating(c);
    }
    setFloatingRule(true);
  }
}
