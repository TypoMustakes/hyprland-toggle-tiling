#include <iostream>
#include "../include/HyprlandService.h"
#include <unistd.h>

int main(int, char**){
  Workspace w = HyprlandService::getCurrentWorkspace();
  std::cout << "Active workspace:" << std::endl;
  std::cout << "  id: " << w.id << std::endl;
  std::cout << "  name: " << w.name << std::endl;
  std::cout << "  monitor: " << w.monitor << std::endl;
  std::cout << "  monitorID: " << w.monitorID << std::endl;
  std::cout << "  windows: " << w.windows << std::endl;
  std::cout << "  hasfullscreen: " << w.hasfullscreen << std::endl;
  std::cout << "  lastwindow: " << w.lastwindow << std::endl;
  std::cout << "  lastwindowtitle: " << w.lastwindowtitle << std::endl;
  std::cout << "  ispersistent: " << w.ispersistent << std::endl;
  std::cout << std::endl;

  std::cout << "---------------------------------------------" << std::endl << std::endl;

  std::list<Client> clients = HyprlandService::getClients();
  for (const auto& c : clients) {
      std::cout << "Client:" << std::endl;
      std::cout << "  address: " << c.address << std::endl;
      std::cout << "  mapped: " << c.mapped << std::endl;
      std::cout << "  hidden: " << c.hidden << std::endl;
      std::cout << "  size: [" << c.size[0] << ", " << c.size[1] << "]" << std::endl;
      std::cout << "  workspace.id: " << c.workspace.id << std::endl;
      std::cout << "  workspace.name: " << c.workspace.name << std::endl;
      std::cout << "  floating: " << c.floating << std::endl;
      std::cout << "  pseudo: " << c.pseudo << std::endl;
      std::cout << "  monitor: " << c.monitor << std::endl;
      std::cout << "  className: " << c.className << std::endl;
      std::cout << "  title: " << c.title << std::endl;
      std::cout << "  initialClass: " << c.initialClass << std::endl;
      std::cout << "  initialTitle: " << c.initialTitle << std::endl;
      std::cout << "  pid: " << c.pid << std::endl;
      std::cout << "  xwayland: " << c.xwayland << std::endl;
      std::cout << "  pinned: " << c.pinned << std::endl;
      std::cout << "  fullscreen: " << c.fullscreen << std::endl;
      std::cout << "  fullscreenClient: " << c.fullscreenClient << std::endl;
      std::cout << "  swallowing: " << c.swallowing << std::endl;
      std::cout << "  focusHistory: " << c.focusHistory << std::endl;
      std::cout << "  inhibitingIdle: " << c.inhibitingIdle << std::endl;
      std::cout << "  xdgTag: " << c.xdgTag << std::endl;
      std::cout << "  xdgDescription: " << c.xdgDescription << std::endl;
      std::cout << std::endl;
    }

  std::cout << "---------------------------------------------" << std::endl << std::endl;

  std::list<Client> activeClients = HyprlandService::getClientsOnActiveWorkspace();
  for (const auto& c : activeClients) {
      std::cout << "Active client:" << std::endl;
      std::cout << "  workspace.id: " << c.workspace.id << std::endl;
      std::cout << "  workspace.name: " << c.workspace.name << std::endl;
      std::cout << "  className: " << c.className << std::endl;
      std::cout << "  title: " << c.title << std::endl;
      std::cout << std::endl;
    }


  std::cout << "Setting " << activeClients.front().className << " into floating mode..." << std::endl;
  sleep(2);
  HyprlandService::setClientFloating(activeClients.front());

  std::cout << "Setting " << activeClients.front().className << " into tiled mode..." << std::endl;
  sleep(2);
  HyprlandService::setClientTiled(activeClients.front());

  std::cout << "Toggling floating mode for " << activeClients.front().className << " ..." << std::endl;
  sleep(2);
  HyprlandService::toggleClientFloating(activeClients.front());

  std::cout << "Toggling floating mode for " << activeClients.front().className << " once more..." << std::endl;
  sleep(2);
  HyprlandService::toggleClientFloating(activeClients.front());
}
