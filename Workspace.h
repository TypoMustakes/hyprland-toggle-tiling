#ifndef WORKSPACE_H
#define WORKSPACE_H
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Workspace {
public:
  int id;
  std::string name;
  std::string monitor;
  int monitorID;
  int windows;
  bool hasfullscreen;
  std::string lastwindow;
  std::string lastwindowtitle;
  bool ispersistent;

  friend void from_json(const json& j, Workspace& workspace);
};

#endif
