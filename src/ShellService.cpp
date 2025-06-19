#include "../include/ShellService.h"
#include <pwd.h>
#include <unistd.h>

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

std::string ShellService::getHomePath()
{
  char* home = getenv("HOME");
  if (home && *home) {
      return std::string(home);
  }

  // Fallback: try to get home directory from passwd if HOME is not set
  // This assumes that the 'htt' process is ran with the user as the process owner. Should it be run with systemd or some other wonky method, it will behave unexpectedly
  struct passwd* pw = getpwuid(getuid());
  if (pw && pw->pw_dir) {
      return std::string(pw->pw_dir);
  }

  // As a last resort, exit
  exit(1);
}