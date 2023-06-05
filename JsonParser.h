#pragma once

#include<string>
#include<vector>

using namespace std;

class JsonP; // 一个JSON对象
class JsonValue;
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
    void insertItemToObject(JsonItem* item);
};

class JsonValue{
};

class JsonItem
{
    string key;
    JsonValue value;
};

class ValueBool:public JsonValue{
    bool value;
};

class ValueNull:public JsonValue{
    static const char* value;
};
const char *ValueNull::value = "null";

class ValueInt:public JsonValue{
    int value;
};

class ValueDouble:public JsonValue{
    double value;
};

class ValueString:public JsonValue{
    string value;
};

class ValueJson:public JsonValue{
    JsonP* value;
};

class ValueArray:public JsonValue{
    vector<JsonValue*> value;
};