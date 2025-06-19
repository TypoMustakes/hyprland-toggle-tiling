#include <iostream>
#include "../include/HyprlandService.h"

int main(int argc, char** argv){
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <config_file_path>\n";
    exit(1);
  }

  HyprlandService::setConfigFilePath(argv[1]);

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