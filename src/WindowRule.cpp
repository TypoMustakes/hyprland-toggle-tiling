#include <algorithm>
#include "../include/WindowRule.h"

std::string WindowRule::toString() {
    std::string mode = this->tile ? "tile" : "float";

    return "windowrule = " + mode + ", onworkspace:" + std::to_string(this->workspaceID);
};

WindowRule WindowRule::parse(std::string ruleStr) {
    WindowRule rule;
    // Remove spaces for easier parsing
    ruleStr.erase(std::remove(ruleStr.begin(), ruleStr.end(), ' '), ruleStr.end());

    // Find mode
    auto modePos = ruleStr.find("windowrule=");
    if (modePos != std::string::npos) {
        auto commaPos = ruleStr.find(',', modePos);
        std::string mode = ruleStr.substr(modePos + 11, commaPos - (modePos + 11));
        rule.tile = (mode == "tile");
    }

    // Find workspace
    auto wsPos = ruleStr.find("onworkspace:");
    if (wsPos != std::string::npos) {
        std::string wsStr = ruleStr.substr(wsPos + 12);
        rule.workspaceID = std::stoi(wsStr);
    }

    return rule;
}