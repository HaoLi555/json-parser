#include"JsonParser.h"

// void JsonP::insertItemToObject(JsonItem* item){
//     this->items.push_back(item);
// }

// @疑问：声明与定义
JsonItem::JsonItem(const char *_key, void *_value_ptr){
    string s(_key);
    key = s;
    value_ptr = _value_ptr;
}

void JsonP::insertNull(const char *key){
    ValueNull *vp = new ValueNull();
    JsonItem *i = new JsonItem(key, vp);
    this->items.push_back(i);
}
