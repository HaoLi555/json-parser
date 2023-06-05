#pragma once

#include<string>
#include<vector>

using namespace std;

class JsonP; // 一个JSON对象
// class JsonValue;
class JsonItem; // 一个键值对
// class ValueBool;
// class ValueNull;
// class ValueInt;
// class ValueDouble;
// class ValueString;
// class ValueJson; // 值是嵌套的JSON对象
class ValueArray;

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

class JsonP{
    vector<JsonItem *> items;
public:
    // void insertItemToObject(JsonItem* item);
    void insertNull(const char *key);
    void insertBool(const char *key, bool value);
    void insertInt(const char *key, int value);
};

// class JsonValue{
// };

class JsonItem
{
    string key;
    ValueType type;
    void *value_ptr;
public:
    JsonItem(const char *_key,ValueType _type, void*_value_ptr);
};

// class ValueBool{
// public:
//     bool value;
//     ValueBool(bool _value):value(_value){}
// };

// class ValueNull{
// public:
//     static const char* value;
// };
// const char *ValueNull::value = "null";

// class ValueInt{
// public:
//     int value;
//     ValueInt(int _value):value(_value){}
// };

// class ValueDouble{
//     double value;
// };

// class ValueString{
//     string value;
// };

// class ValueJson{
//     JsonP* value;
// };

class ValueArray{
    vector<void*> value;
};