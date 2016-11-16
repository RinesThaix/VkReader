/**
 *
 * @author 0xC0deBabe <iam@kostya.sexy>
 */
#include <string>
#include <iostream>
#include <rapidjson/document.h>

#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

using namespace std;
using namespace rapidjson;

class JsonObject {
    
    friend class JsonRetriever;
    
private:
    Value* json;
    
public:
    
    /**
     * Пропарсить информацию в формате json с заданного url-адреса и сохранить все в себя.
     * @param url адрес.
     */
    void parseFromUrl(string url);
    
    /**
     * Пропарсить информацию в формате json, являющуюся ответом на определенный запрос к VK-API.
     * При использовании этого метода в конец url-адреса будет автоматически подставлено
     * &access_token=<токен доступа, указанный в файле конфигурации>.
     * @param method название метода с параметрами (например, messages.get?count=10).
     */
    void parseFromVkApi(string method);
    
    /**
     * Если в нашем json-объекте есть другие json-объекты, через этот метод
     * можно выгрузить внутренний json-объект в JsonObject, чтобы дальше работать с ним.
     * @param jsonObject ссылка на JsonObject, в который следует выгрузить json-объект.
     * @param name название поля, значение которого и является json-объектом.
     * @return ссылку на переданный аргументом JsonObject.
     */
    JsonObject& loadJsonObject(JsonObject& jsonObject, string name);
    
    /**
     * Если в нашем json-объекте есть другие json-объекты, через этот метод
     * можно выгрузить внутренний json-объект в JsonObject, чтобы дальше работать с ним.
     * Метод отличается от loadJsonObject(JsonObject& jsonObject, string name) (предыдущего) тем,
     * что в данном случае данный JsonObject (из которого используется метод) является массивом (то есть JsonArray),
     * и доступ к его элементам осуществляется не по именам, но по индексам в массиве.
     * @param jsonObject ссылка на JsonObject, в который следует выгрузить json-объект.
     * @param id индекс ячейки массива, являющейся json-объектом.
     * @return ссылку на переданный аргументом JsonObject.
     */
    JsonObject& loadJsonObject(JsonObject& jsonObject, int id);
    
    /**
     * Парсит json-объект из конкретно данной строки (никуда не подключаясь и т.д.,
     * как это делают все другие parse-методы класса).
     * @param json информация в формате json, которую необходимо пропарсить.
     */
    void parseFromString(string json);
    
    /**
     * Проверка на то, содержатся ли в данном json'e данные с указанным ключом.
     * @param name ключ.
     * @return true, если содержатся.
     */
    bool contains(string name);
    
    /**
     * Получить строку по указанному ключу.
     * @param name ключ.
     * @return искомая строка.
     */
    string getString(string name);
    
    /**
     * Получить целое число по указанному ключу.
     * @param name ключ.
     * @return искомое число.
     */
    int getInt(string name);
    
    /**
     * Получить число с плавающей точкой по указанному ключу.
     * @param name ключ.
     * @return искомое число.
     */
    double getDouble(string name);
    
    /**
     * Получить логическое значение по указанному ключу.
     * @param name ключ.
     * @return искомое значение.
     */
    bool getBoolean(string name);
    
    /**
     * Получить переменную требуемого типа по указанному ключу.
     * @param name ключ.
     * @return искомую переменную.
     */
    template <typename T>
    T get(string name);
    
    /**
     * Если данный JsonObject является на самом деле массивом (JsonArray), данный
     * метод может быть использован, чтобы вернуть его размер.
     * @return размер данного json-массива.
     */
    int getArraySize();
    
    /**
     * Функция для получения указателя на Value из библиотеки rapidjson, на основе
     * которого построены все методы данного класса.
     * @return указатель на Value из rapidjson.
     */
    Value* getHandle();
    
    /**
     * В теории, в этой функции должно происходить удаление указателя на getHandle(),
     * поскольку при каждом парсинге создается new Document(), однако пока не очень ясно,
     * как это адекватно сделать, так что функция пока пуста.
     */
    void invalidate() {
        
    }
    
};

#endif /* JSON_OBJECT_H */

