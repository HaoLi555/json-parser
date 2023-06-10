#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <sstream>

using namespace std;

enum ValueType
{
    Bool,
    Null,
    Int,
    Double,
    String,
    Object,
    Array
};

class JsonItem;
class JsonObject;     // 一个JSON对象
class JsonArray;      // 一个JSON数组
class JsonObjectItem; // 一个键值对
class JsonArrayItem;  // 一个值

class JsonItem
{

public:
    ValueType type;
    void *value_ptr;

    bool isItemNull();
    optional<bool> getBoolItem();
    optional<int> getIntItem();
    optional<double> getDoubleItem();
    optional<string> getStringItem();
    optional<JsonObject *> getJsonObjectItem();
    optional<JsonArray *> getJsonArrayItem();

    virtual ~JsonItem()
    {
        if (type != ValueType::Object && type != ValueType::Array && type != ValueType::Null)
            delete value_ptr;
    }
};

class JsonObjectItem : public JsonItem
{

public:
    string key;

    JsonObjectItem(const char *_key, ValueType _type, void *_value_ptr);
    JsonObjectItem(string _key, ValueType _type, void *_value_ptr);

    virtual ~JsonObjectItem() {}

    void printItem(int depth);
};

class JsonArrayItem : public JsonItem
{
public:
    JsonArrayItem(ValueType _type, void *_value_ptr);

    virtual ~JsonArrayItem() {}

    void printItem(int depth);
};

class JsonObject
{

public:
    vector<JsonObjectItem *> items;

    void insertNull(const char *key);
    void insertBool(const char *key, bool value);
    void insertInt(const char *key, int value);
    void insertDouble(const char *key, double value);
    void insertString(const char *key, const char *value);
    void insertJson(const char *key, JsonObject *value);
    void insertArray(const char *key, JsonArray *value);

    void insertItem(JsonObjectItem *i);
    void removeItem(const char *key);

    JsonObjectItem *getItemByName(const char *key);

    void dump(const char *file_name);
    void parseObject(const char *file_name);

    ~JsonObject()
    {
        for (auto i : items)
            delete i;
    }
};

class JsonArray
{
public:
    vector<JsonArrayItem *> items;

    void addNull();
    void addBool(bool value);
    void addInt(int value);
    void addDouble(double value);
    void addString(const char *value);
    void addJson(JsonObject *value);
    void addArray(JsonArray *value);

    void insertItem(JsonArrayItem *i);
    void removeItem(int index);

    JsonArrayItem *getItemByIndex(int index);

    ~JsonArray()
    {
        for (auto i : items)
            delete i;
    }
};

JsonObjectItem *parseObjectItem(stringstream &sstream);
JsonArrayItem *parseArrayItem(stringstream &sstream);
