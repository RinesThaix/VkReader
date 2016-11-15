/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <vector>

using namespace std;

#ifndef GLOBAL_UTILS_H
#define GLOBAL_UTILS_H

class GlobalUtils {
    
private:
    static string ios(int i);
    
public:
    
    static vector<string> split(const string& s, char delimiter);
    
    static void sendMessageTo(bool multiChat, int id, string msg);
    
    static string formatTime(long long int time);
    
};

#endif /* GLOBAL_UTILS_H */

