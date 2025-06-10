#include "../include/HyprlandService.h"

using json = nlohmann::json;

std::string HyprlandService::exec(const std::string& command) {
  char buffer[128];
  std::string result = "";

  FILE* pipe = popen(command.c_str(), "r");
  if (!pipe) {
	return "popen failed";
  }

  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
	result += buffer;
  }

  int status = pclose(pipe);
  if (status == -1) {
	return "Error closing pipe";
  }

  return result;
};

Workspace HyprlandService::getCurrentWorkspace() {
  json j = json::parse(exec(HYPRCTL_BINARY " activeworkspace -j"));
  return j.get<Workspace>();
};

std::list<Client> HyprlandService::getClients() {
  json j = json::parse(exec(HYPRCTL_BINARY " clients -j"));
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
  exec(HYPRCTL_BINARY " dispatch setfloating address:" + c.address);
};

void HyprlandService::setClientTiled(Client& c) {
  exec(HYPRCTL_BINARY " dispatch settiled address:" + c.address);
}

void HyprlandService::toggleClientFloating(Client& c) {
  exec("/usr/bin/hyprctl dispatch togglefloating address:" + c.address);
};