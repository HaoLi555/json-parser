#include"JsonParser.h"

// void JsonP::insertItemToObject(JsonItem* item){
//     this->items.push_back(item);
// }

// @疑问：声明与定义
JsonItem::JsonItem(const char *_key,ValueType _type, void *_value_ptr){
    string s(_key);
    key = s;
    type = _type;
    value_ptr = _value_ptr;
}

void JsonP::insertNull(const char *key){
    // ValueNull *vp = new ValueNull();
    JsonItem *i = new JsonItem(key,Null ,nullptr);
    this->items.push_back(i);
}

void JsonP::insertBool(const char *key, bool value){
    bool *vp = new bool(value);
    JsonItem *i = new JsonItem(key, Bool, vp);
    this->items.push_back(i);
}

void JsonP::insertInt(const char *key, int value){
    int *vp = new int(value);
    JsonItem *i = new JsonItem(key, Bool, vp);
    this->items.push_back(i);
}

