/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "global_settings.h"
#include "global_utils.h"
#include "logger.h"

using namespace std;

bool debugMode = false;

std::string token;
int myId;

void GlobalSettings::preloadSettings() {
    ifstream ifs;
    ifs.open("vkreader.settings");
    string line;
    while(getline(ifs, line)) {
        vector<string> split = GlobalUtils::split(line, '=');
        bool set = true;
        if(split[0] == "token")
            token = split[1];
        else if(split[0] == "my_id") {
            myId = stoi(split[1]);
        }else {
            Logger::warn("Unknown param was read from the settings file: '%s'\n", split[0].c_str());
            set = false;
        }
        if(set)
            Logger::log("Param '%s' has been loaded from the settings file!\n", split[0].c_str());
    }
}

string GlobalSettings::getToken() {
    return token;
}

int GlobalSettings::getMyId() {
    return myId;
}

bool GlobalSettings::isInDebugMode() {
    return debugMode;
}

void GlobalSettings::toggleDebugMode() {
    debugMode = !debugMode;
}