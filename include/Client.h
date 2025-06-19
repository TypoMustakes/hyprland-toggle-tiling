#ifndef CLIENT_H
#define CLIENT_H

#include <array>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct WorkspaceSignature {
 public:
  int id;
  std::string name;

  friend void from_json(const json& j, WorkspaceSignature& ws);
};

class Client {
 public:
  std::string address;
  bool mapped;
  bool hidden;
  std::array<int, 2> size;
  WorkspaceSignature workspace;
  bool floating;
  bool pseudo;
  int monitor;
  std::string className;
  std::string title;
  std::string initialClass;
  std::string initialTitle;
  int pid;
  bool xwayland;
  bool pinned;
  int fullscreen;
  int fullscreenClient;
  std::string swallowing;
  int focusHistory;
  bool inhibitingIdle;
  std::string xdgTag;
  std::string xdgDescription;

  friend void from_json(const json& j, Client& client);
};

#endif
