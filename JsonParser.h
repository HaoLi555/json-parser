#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <sstream>

using namespace std;

// JSON格式的变量类型
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

class JsonItem;       // JsonArrayItem和JsonObjectItem的父类
class JsonObject;     // 一个JSON对象
class JsonArray;      // 一个JSON数组
class JsonObjectItem; // 一个键值对
class JsonArrayItem;  // 一个值

class JsonItem
{

public:
    ValueType type;
    void *value_ptr;

    // 下列函数用于获取具体变量值——实际应用中可以利用这些函数获取load的.json文件中的变量

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

    // 用于实现持久化存储，参数用于格式化输出，代表深度，进而确定前面需要多少个tab
    void printItem(int depth);
};

class JsonArrayItem : public JsonItem
{
public:
    JsonArrayItem(ValueType _type, void *_value_ptr);

    virtual ~JsonArrayItem() {}

    // 用于实现持久化存储，参数用于格式化输出，代表深度，进而确定前面需要多少个tab
    void printItem(int depth);
};

class JsonObject
{

public:
    vector<JsonObjectItem *> items;

    // 下列函数用于向一个JsonObject对象中添加键值对，实际可用于将某些数据转化为一个JsonObject对象然后用dump实现持久化储存

    void insertNull(const char *key);
    void insertBool(const char *key, bool value);
    void insertInt(const char *key, int value);
    void insertDouble(const char *key, double value);
    void insertString(const char *key, const char *value);
    void insertJson(const char *key, JsonObject *value);
    void insertArray(const char *key, JsonArray *value);

    void insertItem(JsonObjectItem *i);
    // 删除某个键值对
    void removeItem(const char *key);

    // 由key索引到键值对，进而可以获得变量值
    JsonObjectItem *getItemByName(const char *key);

    // 导出文件，可以实现持久化存储
    void dump(const char *file_name);
    // 从文件中解析导入
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

    // 下列函数用于向一个JsonArray对象中添加变量，实际可用于实现持久化储存

    void addNull();
    void addBool(bool value);
    void addInt(int value);
    void addDouble(double value);
    void addString(const char *value);
    void addJson(JsonObject *value);
    void addArray(JsonArray *value);

    void insertItem(JsonArrayItem *i);
    // 移除某一项
    void removeItem(int index);
    // 由位置索引变量
    JsonArrayItem *getItemByIndex(int index);

    ~JsonArray()
    {
        for (auto i : items)
            delete i;
    }
};

// 用于实现持久化存储的辅助函数
JsonObjectItem *parseObjectItem(stringstream &sstream);
JsonArrayItem *parseArrayItem(stringstream &sstream);
