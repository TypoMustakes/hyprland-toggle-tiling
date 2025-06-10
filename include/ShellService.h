#ifndef SHELL_SERVICE_H
#define SHELL_SERVICE_H

#include <string>

class ShellService {
    public:
        static std::string exec(const std::string& command);
};

#endif