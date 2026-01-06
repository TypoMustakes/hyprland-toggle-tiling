#include <iostream>
#include "../include/HyprlandService.h"

void help(char* execPath) {
	std::cerr << "Usage: " << execPath << " <config_file_path> (-q)\n\n";
	std::cerr << "-q:\tQuery current windowing mode, don't change anything.\n\tReturns Hyprland window rule active on current workspace.\n\tIf no rule is active, returns a default tiled rule.\n";
    exit(1);
}

int main(int argc, char** argv) {
  if (argc < 2) {
	help(argv[0]);
  }

  HyprlandService::setConfigFilePath(argv[1]);

  if (argc == 3 && argv[2] == std::string("-q")) {
	WindowRule rule = HyprlandService::getActiveWorkspaceRule();
	std::cout << rule.toString() << std::endl;
  }
  else if (argc == 2) {
    	if (HyprlandService::isFloatingRulePresent()) {
    	  for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
    		HyprlandService::setClientTiled(c);
    	  }
    	  HyprlandService::setFloatingRule(false);
    	} else {
    	  for (auto& c : HyprlandService::getClientsOnActiveWorkspace()) {
    		HyprlandService::setClientFloating(c);
    	  }
    	  HyprlandService::setFloatingRule(true);
    	}
  }
  else (help(argv[0]));

  exit(0);
}