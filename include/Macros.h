#ifndef MACROS_H
#define MACROS_H

#define HYPRLAND_CONF_DIR "/home/typo/.config/hypr/"
#define FLOATING_RULE_CONF_FILE HYPRLAND_CONF_DIR "hyprland/floatbydefault.conf"

#define HYPRCTL_BINARY "/usr/bin/hyprctl"
#define NULL_PATH "/dev/null"
#define ECHO_PATH "/usr/bin/echo"
#define CAT_PATH "/usr/bin/cat"

#define FLOATING_RULE "windowrule = float,class:.*"
#define SET_FLOATING_RULE ECHO_PATH " 'windowrule = float,class:.*' > " FLOATING_RULE_CONF_FILE
#define REMOVE_FLOATING_RULE CAT_PATH " " NULL_PATH " > " FLOATING_RULE_CONF_FILE

#endif