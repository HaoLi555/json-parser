#pragma once

#include <string>
#include <vector>

using namespace std;

enum ValueType
{
    Bool,
    Null,
    Int,
    Double,
    String,
    Json,
    Array
};

class JsonObject;      // 一个JSON对象
class JsonArray; // 一个JSON数组
class JsonObjectItem;   // 一个键值对
class JsonArrayItem;  // 一个值

class JsonObject
{
    vector<JsonObjectItem *> items;

public:
    void insertNull(const char *key);
    void insertBool(const char *key, bool value);
    void insertInt(const char *key, int value);
    void insertDouble(const char *key, double value);
    void insertString(const char *key, const char *value);
    void insertJson(const char *key, JsonObject *value);
    void insertArray(const char *key, JsonArray *value);



    void dump(const char *file_name);
};

class JsonObjectItem
{
    string key;
    ValueType type;
    void *value_ptr;

public:
    JsonObjectItem(const char *_key, ValueType _type, void *_value_ptr);
};

class JsonArrayItem
{
public:
    ValueType type;
    void *value;
    JsonArrayItem(ValueType _type, void *_value);
};

class JsonArray
{
public:
    vector<JsonArrayItem *> array;
    void addNull();
    void addBool(bool value);
    void addInt(int value);
    void addDouble(double value);
    void addString(const char *value);
    void addJson(JsonObject *value);
    void addArray(JsonArray *value);

    void dump(const char *file_name);

};