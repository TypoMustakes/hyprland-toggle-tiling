#include "Workspace.h"

void from_json(const nlohmann::json &j, Workspace &w) {
  j.at("id").get_to(w.id);
  j.at("name").get_to(w.name);
  j.at("monitor").get_to(w.monitor);
  j.at("monitorID").get_to(w.monitorID);
  j.at("windows").get_to(w.windows);
  j.at("hasfullscreen").get_to(w.hasfullscreen);
  j.at("lastwindow").get_to(w.lastwindow);
  j.at("lastwindowtitle").get_to(w.lastwindowtitle);
  j.at("ispersistent").get_to(w.ispersistent);
}
