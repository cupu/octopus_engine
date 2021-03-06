#include "../include/configurations.hpp"
#include "../include/log.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <exception>
#include <fstream>
#include <typeinfo>

boost::property_tree::ptree Configurations::pt;
std::unordered_map<std::string, boost::any> Configurations::defaults;

void Configurations::parse(const std::string& filename) {
    std::ifstream input(filename.c_str());
    if (input) {
        boost::property_tree::ini_parser::read_ini(input, pt);
    } else {
        LOGGER_W << "Couldn't open config file " << filename;
    }
    defaults["game.title"] = std::string("Untitled");
    defaults["game.font"] = std::string("Unibody 8-Italic.otf");
	defaults["game.font-size"] = 8;
    defaults["game.screen-width"] = 640;
    defaults["game.screen-height"] = 480;
    defaults["game.fullscreen"] = false;
    defaults["game.npcs-file"] = std::string();
    // Scaling modes: aspect, window, stretch
    defaults["game.scale-mode"] = std::string("window");
    defaults["game.vertex-shader"] = std::string();
    defaults["game.fragment-shader"] = std::string();
    defaults["game.pause-vertex-shader"] = std::string();
    defaults["game.pause-fragment-shader"] = std::string();
    defaults["game.pause-unfocused"] = true;
    defaults["game.save-folder"] = std::string();
    defaults["controls.gamepad-enabled"] = true;
    defaults["controls.action-button"] = std::string("a");
    defaults["controls.mapping-file"] = std::string("keymap.ini");
    defaults["logging.filename"] = std::string("game.log");
    defaults["logging.level"] = std::string("debug");
    defaults["debug.width"] = 320;
    defaults["debug.height"] = 240;
    defaults["debug.show-fps"] = true;
    defaults["debug.show-time"] = false;
    defaults["debug.logic-fps"] = 40;
    defaults["debug.time-multiplier"] = 0.5f;
    defaults["debug.pathfinding-sprite"] = std::string();
    defaults["startup.map"] = std::string();
    defaults["startup.player-sprite"] = std::string();
    defaults["startup.player-position-x"] = 70.0f;
    defaults["startup.player-position-y"] = 50.0f;
    defaults["startup.tint-color"] = std::string("00000000");
    defaults["startup.clear-color"] = std::string("00000000");
    defaults["startup.scripts-list"] = std::string();
}

std::string Configurations::get_string(const std::string& name) {
    if (defaults.find(name) == defaults.end())
        return get<std::string>(name);
    // Ugly...
    auto& type = defaults[name].type();
    if (type == typeid(std::string))
        return get<std::string>(name);
    if (type == typeid(int))
        return boost::lexical_cast<std::string>(get<int>(name));
    if (type == typeid(float))
        return boost::lexical_cast<std::string>(get<float>(name));
    if (type == typeid(bool))
        return boost::lexical_cast<std::string>(get<bool>(name));
    return "";
}
