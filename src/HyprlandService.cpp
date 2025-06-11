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

  for (auto& line : FileService::readLines(ShellService::getHomePath()+FLOATING_RULE_CONF_FILE)) {
    rules.push_back(WindowRule::parse(line));
  }

  return rules;
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

//on = true -> creates a window rule to ENABLE floating mode for currently active workspace
//on = false -> creates a window rule to DISABLE floating mode for currently active workspace
void HyprlandService::setFloatingRule(bool on) {
  WindowRule rule {.tile = !on, .workspaceID = getCurrentWorkspace().id};
  auto conflictingRule = findConflictingRule(rule);
  if (conflictingRule.has_value()) {
    removeRule(conflictingRule.value());
  }

  FileService::appendToFile(
    ShellService::getHomePath() + FLOATING_RULE_CONF_FILE,
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
      ShellService::getHomePath() + FLOATING_RULE_CONF_FILE,
      foundIndex
    );
  }

  //else: rule not found, do nothing
}

bool HyprlandService::isFloatingRulePresent() {
  //Checks if there's a valid window rule in place that enables floating mode for the currently active workspace
  std::list<WindowRule> rules = getWindowRules();
  int id = getCurrentWorkspace().id;

  for (auto& rule : rules) {
    if (rule.workspaceID == id && rule.tile == false) {
      return true;
    }
  }

  return false;
};