/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <vector>
#include "json_object.h"
#include "global_utils.h"
#include <ctime>

using namespace std;

vector<string> GlobalUtils::split(const string& s, char delimiter) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while((end = s.find(delimiter, start)) != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

void GlobalUtils::sendMessageTo(bool multiChat, int id, string msg) {
    JsonObject json;
    string param = multiChat ? "chat" : "user";
    json.parseFromVkApi("messages.send?message=" + msg + "&" + param + "_id=" + to_string(id));
}

string GlobalUtils::ios(int i) {
    string s = to_string(i);
    if(s.length() == 1)
        s = "0" + s;
    return s;
}

string GlobalUtils::formatTime(long long int time) {
    time_t tt = (time_t) time;
    tm *ltm = localtime(&tt);
    string day = ios(ltm->tm_mday);
    string month = ios(ltm->tm_mon + 1);
    string year = ios(ltm->tm_year - 100);
    string hours = ios(ltm->tm_hour);
    string minutes = ios(ltm->tm_min);
    string seconds = ios(ltm->tm_sec);
    return day + "." + month + "." + year + " " + hours + ":" + minutes + ":" + seconds;
}
