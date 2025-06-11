#ifndef WINDOW_RULE_H
#define WINDOW_RULE_H

#include <string>

class WindowRule {
    public:
        //true -> tiling mode
        //false -> floating mode
        bool tile;
        
        //Which workspace to apply to
        int workspaceID;

        std::string toString();

        static WindowRule parse(std::string);
};

#endif