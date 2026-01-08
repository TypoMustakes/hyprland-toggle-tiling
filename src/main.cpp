#include <iostream>
#include <stdexcept>
#include "../include/HyprlandService.h"

void help(char* execPath) {
	std::cerr << "Usage: " << execPath << " <config_file_path> (flags)\n\n";
	std::cerr << "Flags:\n\n";
	std::cerr << "-q:\t\tQuery current windowing mode, don't change anything.\n\t\tReturns Hyprland window rule active on current workspace.\n\t\tIf no rule is active, returns a default tiled rule.\n\n";
	std::cerr << "-m [integer]:\tMove currently active window to specified workspace.\n\t\tUpon moving, the window will adapt to the windowing mode of the new workspace.\n\t\tDoesn't work with -q.\n";
    exit(1);
}

int main(int argc, char** argv) {
  if (argc >= 2) {
	HyprlandService::setConfigFilePath(argv[1]);

	if (argc == 2) {
	  HyprlandService::toggleFloating();
	}          
	else if (argc == 3 && argv[2] == std::string("-q")) {
	  std::cout << HyprlandService::getActiveWorkspaceRule().toString() << std::endl;
	} else if (argc == 4 && argv[2] == std::string("-m")) {
	  int workspace = 0;
	  try {
		HyprlandService::moveToWorkspace(std::stoi(argv[3]));
	  } catch (std::invalid_argument) {
		help(argv[0]);
	  }
	} else {
	  help(argv[0]);
	}
  } else {
	help(argv[0]);
  }

  exit(0);
}
