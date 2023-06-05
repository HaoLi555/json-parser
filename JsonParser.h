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

class JsonP;      // 一个JSON对象
class ValueArray; // 一个JSON数组
class JsonItem;   // 一个键值对
class JsonValue;  // 一个值

class JsonP
{
    vector<JsonItem *> items;

public:
    void insertNull(const char *key);
    void insertBool(const char *key, bool value);
    void insertInt(const char *key, int value);
    void insertDouble(const char *key, double value);
    void insertString(const char *key, const char *value);
    void insertJson(const char *key, JsonP *value);
    void insertArray(const char *key, ValueArray *value);
};

class JsonItem
{
    string key;
    ValueType type;
    void *value_ptr;

public:
    JsonItem(const char *_key, ValueType _type, void *_value_ptr);
};

class JsonValue
{
public:
    ValueType type;
    void *value;
    JsonValue(ValueType _type, void *_value);
};

class ValueArray
{
public:
    vector<JsonValue *> array;
    void addNull();
    void addBool(bool value);
    void addInt(int value);
    void addDouble(double value);
    void addString(const char *value);
    void addJson(JsonP *value);
    void addArray(ValueArray *value);
};