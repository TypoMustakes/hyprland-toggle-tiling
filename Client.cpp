#include "Client.h"

void from_json(const json& j, WorkspaceSignature& ws) {
  j.at("id").get_to(ws.id);
  j.at("name").get_to(ws.name);
}

void from_json(const json& j, Client& client) {
  j.at("address").get_to(client.address);
  j.at("mapped").get_to(client.mapped);
  j.at("hidden").get_to(client.hidden);
  j.at("size").get_to(client.size);
  j.at("workspace").get_to(client.workspace);
  j.at("floating").get_to(client.floating);
  j.at("pseudo").get_to(client.pseudo);
  j.at("monitor").get_to(client.monitor);
  j.at("class").get_to(client.className); // Maps "class" JSON field to className
  j.at("title").get_to(client.title);
  j.at("initialClass").get_to(client.initialClass);
  j.at("initialTitle").get_to(client.initialTitle);
  j.at("pid").get_to(client.pid);
  j.at("xwayland").get_to(client.xwayland);
  j.at("pinned").get_to(client.pinned);
  j.at("fullscreen").get_to(client.fullscreen);
  j.at("fullscreenClient").get_to(client.fullscreenClient);
  j.at("swallowing").get_to(client.swallowing);
  j.at("focusHistoryID").get_to(client.focusHistory);
  j.at("inhibitingIdle").get_to(client.inhibitingIdle);
  j.at("xdgTag").get_to(client.xdgTag);
  j.at("xdgDescription").get_to(client.xdgDescription);
}
