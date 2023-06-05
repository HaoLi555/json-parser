#pragma once

#include<string>
#include<vector>

using namespace std;

class JsonP; // 一个JSON对象
// class JsonValue;
class JsonItem; // 一个键值对
class ValueBool;
class ValueNull;
class ValueInt;
class ValueDouble;
class ValueString;
class ValueJson; // 值是嵌套的JSON对象
class ValueArray;


class JsonP{
    vector<JsonItem *> items;
public:
    // void insertItemToObject(JsonItem* item);
    void insertNull(const char *key);
};

// class JsonValue{
// };

class JsonItem
{
    string key;
    void* value_ptr;
public:
    JsonItem(const char *_key, void*_value_ptr);
};

class ValueBool{
    bool value;
};

class ValueNull{
public:
    static const char* value;
};
const char *ValueNull::value = "null";

class ValueInt{
    int value;
};

class ValueDouble{
    double value;
};

class ValueString{
    string value;
};

class ValueJson{
    JsonP* value;
};

class ValueArray{
    vector<void*> value;
};