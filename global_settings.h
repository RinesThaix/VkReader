/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>

#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

class GlobalSettings {
    
public:
    
    static void preloadSettings();
    
    static std::string getToken();
    
    static int getMyId();
    
    static bool isInDebugMode();
    
    static void toggleDebugMode();
    
};

#endif /* GLOBAL_SETTINGS_H */

