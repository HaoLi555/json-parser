#include "JsonParser.h"



// @疑问：声明与定义
JsonItem::JsonItem(const char *_key, ValueType _type, void *_value_ptr)
{
    string s(_key);
    key = s;
    type = _type;
    value_ptr = _value_ptr;
}

void JsonObject::insertNull(const char *key)
{
    // ValueNull *vp = new ValueNull();
    JsonItem *i = new JsonItem(key, Null, nullptr);
    this->items.push_back(i);
}

void JsonObject::insertBool(const char *key, bool value)
{
    bool *vp = new bool(value);
    JsonItem *i = new JsonItem(key, Bool, vp);
    this->items.push_back(i);
}

void JsonObject::insertInt(const char *key, int value)
{
    int *vp = new int(value);
    JsonItem *i = new JsonItem(key, Int, vp);
    this->items.push_back(i);
}

void JsonObject::insertDouble(const char *key, double value)
{
    double *vp = new double(value);
    JsonItem *i = new JsonItem(key, Double, vp);
    this->items.push_back(i);
}

void JsonObject::insertString(const char *key, const char *value)
{
    string *vp = new string(value);
    JsonItem *i = new JsonItem(key, String, vp);
    this->items.push_back(i);
}

void JsonObject::insertJson(const char *key, JsonObject *value)
{
    JsonItem *i = new JsonItem(key, Json, value);
    this->items.push_back(i);
}

void JsonObject::insertArray(const char *key, JsonArray *value)
{
    JsonItem *i = new JsonItem(key, Json, value);
    this->items.push_back(i);
}

JsonValue::JsonValue(ValueType _type, void *_value)
{
    type = _type;
    value = _value;
}

void JsonArray::addNull()
{
    JsonValue *v = new JsonValue(Null, nullptr);
    this->array.push_back(v);
}

void JsonArray::addBool(bool value)
{
    bool *b = new bool(value);
    JsonValue *v = new JsonValue(Bool, b);
    this->array.push_back(v);
}

void JsonArray::addInt(int value)
{
    int *i = new int(value);
    JsonValue *v = new JsonValue(Bool, i);
    this->array.push_back(v);
}

void JsonArray::addDouble(double value)
{
    double *d = new double(value);
    JsonValue *v = new JsonValue(Double, d);
    this->array.push_back(v);
}

void JsonArray::addString(const char *value)
{
    string *s = new string(value);
    JsonValue *v = new JsonValue(String, s);
    this->array.push_back(v);
}

void JsonArray::addJson(JsonObject *value)
{
    JsonValue *v = new JsonValue(Json, value);
    this->array.push_back(v);
}

void JsonArray::addArray(JsonArray *value)
{
    JsonValue *v = new JsonValue(Json, value);
    this->array.push_back(v);
}