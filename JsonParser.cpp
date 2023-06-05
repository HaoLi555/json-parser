#include "JsonParser.h"



// @疑问：声明与定义
JsonItem::JsonItem(const char *_key, ValueType _type, void *_value_ptr)
{
    string s(_key);
    key = s;
    type = _type;
    value_ptr = _value_ptr;
}

void JsonP::insertNull(const char *key)
{
    // ValueNull *vp = new ValueNull();
    JsonItem *i = new JsonItem(key, Null, nullptr);
    this->items.push_back(i);
}

void JsonP::insertBool(const char *key, bool value)
{
    bool *vp = new bool(value);
    JsonItem *i = new JsonItem(key, Bool, vp);
    this->items.push_back(i);
}

void JsonP::insertInt(const char *key, int value)
{
    int *vp = new int(value);
    JsonItem *i = new JsonItem(key, Int, vp);
    this->items.push_back(i);
}

void JsonP::insertDouble(const char *key, double value)
{
    double *vp = new double(value);
    JsonItem *i = new JsonItem(key, Double, vp);
    this->items.push_back(i);
}

void JsonP::insertString(const char *key, const char *value)
{
    string *vp = new string(value);
    JsonItem *i = new JsonItem(key, String, vp);
    this->items.push_back(i);
}

void JsonP::insertJson(const char *key, JsonP *value)
{
    JsonItem *i = new JsonItem(key, Json, value);
    this->items.push_back(i);
}

void JsonP::insertArray(const char *key, ValueArray *value)
{
    JsonItem *i = new JsonItem(key, Json, value);
    this->items.push_back(i);
}

JsonValue::JsonValue(ValueType _type, void *_value)
{
    type = _type;
    value = _value;
}

void ValueArray::addNull()
{
    JsonValue *v = new JsonValue(Null, nullptr);
    this->array.push_back(v);
}

void ValueArray::addBool(bool value)
{
    bool *b = new bool(value);
    JsonValue *v = new JsonValue(Bool, b);
    this->array.push_back(v);
}

void ValueArray::addInt(int value)
{
    int *i = new int(value);
    JsonValue *v = new JsonValue(Bool, i);
    this->array.push_back(v);
}

void ValueArray::addDouble(double value)
{
    double *d = new double(value);
    JsonValue *v = new JsonValue(Double, d);
    this->array.push_back(v);
}

void ValueArray::addString(const char *value)
{
    string *s = new string(value);
    JsonValue *v = new JsonValue(String, s);
    this->array.push_back(v);
}

void ValueArray::addJson(JsonP *value)
{
    JsonValue *v = new JsonValue(Json, value);
    this->array.push_back(v);
}

void ValueArray::addArray(ValueArray *value)
{
    JsonValue *v = new JsonValue(Json, value);
    this->array.push_back(v);
}