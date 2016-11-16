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
    
    /**
     * Разбить строку по разделяющему символу.
     * @param s сама строка.
     * @param delimiter разделяющий символ.
     * @return вектор строк, полученных после разбиения.
     */
    static vector<string> split(const string& s, char delimiter);
    
    /**
     * Отправить сообщение в указанную беседу.
     * @param multiChat true, если указанная беседа является мульти-чатом (то есть не разговором 1х1).
     * @param id идентификатор беседы.
     * @param msg сообщение.
     */
    static void sendMessageTo(bool multiChat, int id, string msg);
    
    /**
     * Форматирование метки времени в читабельную строку.
     * @param time время.
     * @return строку вида dd.MM.yy hh:mm:ss.
     */
    static string formatTime(long long int time);
    
};

#endif /* GLOBAL_UTILS_H */

