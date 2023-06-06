#include "JsonParser.h"



// @疑问：声明与定义
JsonObjectItem::JsonObjectItem(const char *_key, ValueType _type, void *_value_ptr)
{
    string s(_key);
    key = s;
    type = _type;
    value_ptr = _value_ptr;
}

void JsonObject::insertNull(const char *key)
{
    // ValueNull *vp = new ValueNull();
    JsonObjectItem *i = new JsonObjectItem(key, Null, nullptr);
    this->items.push_back(i);
}

void JsonObject::insertBool(const char *key, bool value)
{
    bool *vp = new bool(value);
    JsonObjectItem *i = new JsonObjectItem(key, Bool, vp);
    this->items.push_back(i);
}

void JsonObject::insertInt(const char *key, int value)
{
    int *vp = new int(value);
    JsonObjectItem *i = new JsonObjectItem(key, Int, vp);
    this->items.push_back(i);
}

void JsonObject::insertDouble(const char *key, double value)
{
    double *vp = new double(value);
    JsonObjectItem *i = new JsonObjectItem(key, Double, vp);
    this->items.push_back(i);
}

void JsonObject::insertString(const char *key, const char *value)
{
    string *vp = new string(value);
    JsonObjectItem *i = new JsonObjectItem(key, String, vp);
    this->items.push_back(i);
}

void JsonObject::insertJson(const char *key, JsonObject *value)
{
    JsonObjectItem *i = new JsonObjectItem(key, Json, value);
    this->items.push_back(i);
}

void JsonObject::insertArray(const char *key, JsonArray *value)
{
    JsonObjectItem *i = new JsonObjectItem(key, Json, value);
    this->items.push_back(i);
}

JsonArrayItem::JsonArrayItem(ValueType _type, void *_value)
{
    type = _type;
    value = _value;
}

void JsonArray::addNull()
{
    JsonArrayItem *v = new JsonArrayItem(Null, nullptr);
    this->array.push_back(v);
}

void JsonArray::addBool(bool value)
{
    bool *b = new bool(value);
    JsonArrayItem *v = new JsonArrayItem(Bool, b);
    this->array.push_back(v);
}

void JsonArray::addInt(int value)
{
    int *i = new int(value);
    JsonArrayItem *v = new JsonArrayItem(Bool, i);
    this->array.push_back(v);
}

void JsonArray::addDouble(double value)
{
    double *d = new double(value);
    JsonArrayItem *v = new JsonArrayItem(Double, d);
    this->array.push_back(v);
}

void JsonArray::addString(const char *value)
{
    string *s = new string(value);
    JsonArrayItem *v = new JsonArrayItem(String, s);
    this->array.push_back(v);
}

void JsonArray::addJson(JsonObject *value)
{
    JsonArrayItem *v = new JsonArrayItem(Json, value);
    this->array.push_back(v);
}

void JsonArray::addArray(JsonArray *value)
{
    JsonArrayItem *v = new JsonArrayItem(Json, value);
    this->array.push_back(v);
}

void JsonObject::dump(const char *file_name){
    




}


void JsonArray::dump(const char* file_name){
    


}