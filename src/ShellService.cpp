#include "../include/ShellService.h"

std::string ShellService::exec(const std::string& command) {
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