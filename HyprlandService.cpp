#include "HyprlandService.h"

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
  json j = json::parse(exec("/usr/bin/hyprctl activeworkspace -j"));
  return j.get<Workspace>();
};

std::list<Client> HyprlandService::getClients() {
  json j = json::parse(exec("/usr/bin/hyprctl clients -j"));
  return j.get<std::list<Client>>();
};
