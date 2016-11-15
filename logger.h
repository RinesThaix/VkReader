/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef LOGGER_H
#define LOGGER_H

class Logger {
    
private:
    
    static char* sum(const char* prefix, const char* message) {
        char* result = (char*) malloc(strlen(prefix) + strlen(message) + 1);
        strcpy(result, prefix);
        strcat(result, message);
        return result;
    }
    
public:
    
    static void p(int id) {
        cout << "Debug #" << id << endl;
    }
    
    static void log(const char* message, ...) {
        va_list argptr;
        va_start(argptr, message);
        vfprintf(stdout, sum("[INFO] ", message), argptr);
        va_end(argptr);
    }
    
    static void debug(const char* message, ...) {
        va_list argptr;
        va_start(argptr, message);
        vfprintf(stdout, sum("[DEBUG] ", message), argptr);
        va_end(argptr);
    }
    
    static void warn(const char* message, ...) {
        va_list argptr;
        va_start(argptr, message);
        vfprintf(stderr, sum("[WARN] ", message), argptr);
        va_end(argptr);
    }
    
    static void fatal(const char* message, ...) {
        va_list argptr;
        va_start(argptr, message);
        vfprintf(stderr, sum("[FATAL] ", message), argptr);
        va_end(argptr);
    }
    
};

#endif /* LOGGER_H */

