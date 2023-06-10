#include "JsonParser.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

bool JsonItem::isItemNull()
{

    if (this->type == ValueType::Null)
        return true;
    else
        return false;
}

optional<bool> JsonItem::getBoolItem()
{
    if (type != Bool)
        return nullopt;
    else
    {

        return *((bool *)value_ptr);
    }
}

optional<int> JsonItem::getIntItem()
{
    if (type != Int)
        return nullopt;
    else
    {

        return *((int *)value_ptr);
    }
}

optional<double> JsonItem::getDoubleItem()
{
    if (type != Double)
        return nullopt;
    else
    {

        return *((double *)value_ptr);
    }
}

optional<string> JsonItem::getStringItem()
{
    if (type != String)
        return nullopt;
    else
    {

        return *((string *)value_ptr);
    }
}

optional<JsonObject *> JsonItem::getJsonObjectItem()
{
    if (type != Object)
        return nullopt;
    else
    {

        return (JsonObject *)value_ptr;
    }
}

optional<JsonArray *> JsonItem::getJsonArrayItem()
{
    if (type != Array)
        return nullopt;
    else
    {

        return (JsonArray *)value_ptr;
    }
}

// @疑问：声明与定义
JsonObjectItem::JsonObjectItem(const char *_key, ValueType _type, void *_value_ptr)
{
    string s(_key);
    key = s;
    type = _type;
    value_ptr = _value_ptr;
}

JsonObjectItem::JsonObjectItem(string _key, ValueType _type, void *_value_ptr)
{

    key = _key;
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
    JsonObjectItem *i = new JsonObjectItem(key, Object, value);
    this->items.push_back(i);
}

void JsonObject::insertArray(const char *key, JsonArray *value)
{
    JsonObjectItem *i = new JsonObjectItem(key, Array, value);
    this->items.push_back(i);
}

void JsonObject::insertItem(JsonObjectItem *i)
{
    items.push_back(i);
}

void JsonObject::removeItem(const char *key)
{
    string obj_key(key);
    for (auto it = items.begin(); it != items.end(); it++)
    {
        if (obj_key == (*it)->key)
        {
            delete (*it);
            items.erase(it);
            return;
        }
    }
}

JsonArrayItem::JsonArrayItem(ValueType _type, void *_value_ptr)
{
    type = _type;
    value_ptr = _value_ptr;
}

void JsonArray::addNull()
{
    JsonArrayItem *v = new JsonArrayItem(Null, nullptr);
    this->items.push_back(v);
}

void JsonArray::addBool(bool value)
{
    bool *b = new bool(value);
    JsonArrayItem *v = new JsonArrayItem(Bool, b);
    this->items.push_back(v);
}

void JsonArray::addInt(int value)
{
    int *i = new int(value);
    JsonArrayItem *v = new JsonArrayItem(Bool, i);
    this->items.push_back(v);
}

void JsonArray::addDouble(double value)
{
    double *d = new double(value);
    JsonArrayItem *v = new JsonArrayItem(Double, d);
    this->items.push_back(v);
}

void JsonArray::addString(const char *value)
{
    string *s = new string(value);
    JsonArrayItem *v = new JsonArrayItem(String, s);
    this->items.push_back(v);
}

void JsonArray::addJson(JsonObject *value)
{
    JsonArrayItem *v = new JsonArrayItem(Object, value);
    this->items.push_back(v);
}

void JsonArray::addArray(JsonArray *value)
{
    JsonArrayItem *v = new JsonArrayItem(Array, value);
    this->items.push_back(v);
}

void JsonArray::insertItem(JsonArrayItem *i)
{

    this->items.push_back(i);
}

void JsonArray::removeItem(int index)
{
    auto it = items.begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    delete (*it);
    items.erase(it);
}

// 没查找到时返回空指针
JsonObjectItem *JsonObject::getItemByName(const char *key)
{
    string temp(key);
    for (auto item_ptr : this->items)
    {
        if (temp == item_ptr->key)
        {
            return item_ptr;
        }
    }
    return nullptr;
}

// 没查找到时返回空指针
JsonArrayItem *JsonArray::getItemByIndex(int index)
{
    try
    {
        return this->items[index];
    }
    catch (...)
    {
        return nullptr;
    }
}

void JsonObject::dump(const char *file_name)
{
    FILE *errfp;
    freopen_s(&errfp, file_name, "w", stdout);
    cout << "{" << endl;
    for (int i = 0; i < items.size(); i++)
    {
        items[i]->printItem(1); // 深度为1
        if (i != items.size() - 1)
            cout << "," << endl;
    }
    cout << endl;
    cout << "}";

    // 关闭之前的重定向，仍输出至控制台
    freopen_s(&errfp, "CON", "w", stdout);
}

void JsonObjectItem::printItem(int depth)
{
    for (int i = 0; i < depth; i++)
        cout << "\t";
    cout << "\"";
    cout << key;
    cout << "\"";
    cout << ":";
    switch (type)
    {
    case ValueType::Bool:
        if (*((bool *)value_ptr))
            cout << "true";
        else
            cout << "false";
        break;
    case ValueType::Double:
        cout << *((double *)value_ptr);
        break;
    case ValueType::Int:
        cout << *((int *)value_ptr);
        break;
    case ValueType::Null:
        cout << "null";
        break;
    case ValueType::String:
        cout << "\"" << *((string *)value_ptr) << "\"";
        break;
    case ValueType::Object:
    {
        vector<JsonObjectItem *> &items = ((JsonObject *)value_ptr)->items;
        cout << "{" << endl;
        for (int i = 0; i < items.size(); i++)
        {
            items[i]->printItem(depth + 1);
            if (i != items.size() - 1)
                cout << "," << endl;
        }
        cout << endl;
        for (int i = 0; i < depth; i++)
            cout << "\t";
        cout << "}";
        break;
    }

    case ValueType::Array:
    {
        vector<JsonArrayItem *> &items = ((JsonArray *)value_ptr)->items;
        cout << "[" << endl;
        for (int i = 0; i < items.size(); i++)
        {
            items[i]->printItem(depth + 1);
            if (i != items.size() - 1)
                cout << "," << endl;
        }
        cout << endl;
        for (int i = 0; i < depth; i++)
            cout << "\t";
        cout << "]";
        break;
    }

    default:
        break;
    }
}

void JsonArrayItem::printItem(int depth)
{
    for (int i = 0; i < depth; i++)
        cout << "\t";
    switch (type)
    {
    case ValueType::Bool:
        if (*((bool *)value_ptr))
            cout << "true";
        else
            cout << "false";
        break;
    case ValueType::Double:
        cout << *((double *)value_ptr);
        break;
    case ValueType::Int:
        cout << *((int *)value_ptr);
        break;
    case ValueType::Null:
        cout << "null";
        break;
    case ValueType::String:
        cout << "\"" << *((string *)value_ptr) << "\"";
        break;
    case ValueType::Object:
    {
        vector<JsonObjectItem *> &items = ((JsonObject *)value_ptr)->items;
        cout << "{" << endl;
        for (int i = 0; i < items.size(); i++)
        {
            items[i]->printItem(depth + 1);
            if (i != items.size() - 1)
                cout << "," << endl;
        }
        cout << endl;
        for (int i = 0; i < depth; i++)
            cout << "\t";
        cout << "}";
        break;
    }

    case ValueType::Array:
    {
        vector<JsonArrayItem *> &items = ((JsonArray *)value_ptr)->items;
        cout << "[" << endl;
        for (int i = 0; i < items.size(); i++)
        {
            items[i]->printItem(depth + 1);
            if (i != items.size() - 1)
                cout << "," << endl;
        }
        cout << endl;
        for (int i = 0; i < depth; i++)
            cout << "\t";
        cout << "]";
        break;
    }

    default:
        break;
    }
}

JsonObjectItem *parseObjectItem(stringstream &sstream)
{
    while (sstream.peek() == ' ' || sstream.peek() == '\t' || sstream.peek() == '\n')
        sstream.get();
    string key;
    sstream.get(); // 掠过引号
    while (sstream.peek() != '\"')
    {
        // 这里.get()返回的ASCII码
        key.push_back(sstream.get());
    }
    sstream.get(); // 掠过引号
    while (sstream.peek() != ':')
        sstream.get();
    sstream.get(); // 掠过冒号
    while (sstream.peek() == ' ' || sstream.peek() == '\t' || sstream.peek() == '\n')
        sstream.get();
    switch (sstream.peek())
    {
    case 'n':
    {
        for (int i = 0; i < 4; i++)
        {
            sstream.get();
        }
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::Null, nullptr);
        return ans;
    }
    case 'f':
    {
        for (int i = 0; i < 5; i++)
        {
            sstream.get();
        }
        bool *vp = new bool(false);
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::Bool, vp);
        return ans;
    }
    case 't':
    {
        for (int i = 0; i < 4; i++)
        {
            sstream.get();
        }
        bool *vp = new bool(true);
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::Bool, vp);
        return ans;
    }
    case '\"':
    {
        sstream.get(); // 处理单引号
        string *v = new string;
        while (sstream.peek() != '\"')
        {
            v->push_back(sstream.peek());
            sstream.get();
        }
        sstream.get();
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::String, v);
        return ans;
    }
    case '{':
    {
        sstream.get(); // 处理'{'
        JsonObject *jo = new JsonObject;
        do
        {
            if (sstream.peek() == ',')
                sstream.get();
            jo->insertItem(parseObjectItem(sstream));
            while (sstream.peek() != ',' && sstream.peek() != '}')
                sstream.get();
        } while (sstream.peek() != '}');
        sstream.get(); // 掠过'}'
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::Object, jo);
        return ans;
    }
    case '[':
    {
        sstream.get(); // 处理'['
        JsonArray *ja = new JsonArray;
        do
        {
            if (sstream.peek() == ',')
                sstream.get();
            ja->insertItem(parseArrayItem(sstream));
            while (sstream.peek() != ',' && sstream.peek() != ']')
                sstream.get();
        } while (sstream.peek() != ']');
        sstream.get(); // 掠过']'
        JsonObjectItem *ans = new JsonObjectItem(key, ValueType::Array, ja);
        return ans;
    }
    // 数字
    default:
    {
        string temp;
        bool is_double = false;
        while (sstream.peek() == '+' || sstream.peek() == '-' || sstream.peek() == 'E' || sstream.peek() == 'e' || sstream.peek() == '.' || isdigit(sstream.peek()))
        {
            if (sstream.peek() == 'e' || sstream.peek() == 'E' || sstream.peek() == '.')
                is_double = true;
            temp.push_back(sstream.get());
        }
        JsonObjectItem *ans;
        if (is_double)
        {
            double *d = new double(stod(temp));
            ans = new JsonObjectItem(key, ValueType::Double, d);
        }
        else
        {
            int *i = new int(stoi(temp));
            ans = new JsonObjectItem(key, ValueType::Int, i);
        }
        return ans;
        break;
    }
    }
}

JsonArrayItem *parseArrayItem(stringstream &sstream)
{
    while (sstream.peek() == ' ' || sstream.peek() == '\t' || sstream.peek() == '\n')
        sstream.get();
    switch (sstream.peek())
    {
    case 'n':
    {
        for (int i = 0; i < 4; i++)
        {
            sstream.get();
        }
        JsonArrayItem *ans = new JsonArrayItem(ValueType::Null, nullptr);
        return ans;
    }
    case 'f':
    {
        for (int i = 0; i < 5; i++)
        {
            sstream.get();
        }
        bool *vp = new bool(false);
        JsonArrayItem *ans = new JsonArrayItem(ValueType::Bool, vp);
        return ans;
    }
    case 't':
    {
        for (int i = 0; i < 4; i++)
        {
            sstream.get();
        }
        bool *vp = new bool(true);
        JsonArrayItem *ans = new JsonArrayItem(ValueType::Bool, vp);
        return ans;
    }
    case '\"':
    {
        sstream.get(); // 处理单引号
        string *v = new string;
        while (sstream.peek() != '\"')
        {
            v->push_back(sstream.peek());
            sstream.get();
        }
        sstream.get();
        JsonArrayItem *ans = new JsonArrayItem(ValueType::String, v);
        return ans;
    }
    case '{':
    {
        sstream.get(); // 处理'{'
        JsonObject *jo = new JsonObject;
        do
        {
            if (sstream.peek() == ',')
                sstream.get();
            jo->insertItem(parseObjectItem(sstream));
            while (sstream.peek() != ',' && sstream.peek() != '}')
                sstream.get();
        } while (sstream.peek() != '}');
        sstream.get(); // 掠过'}'
        JsonArrayItem *ans = new JsonArrayItem(ValueType::Object, jo);
        return ans;
    }
    case '[':
    {
        sstream.get(); // 处理'['
        JsonArray *ja = new JsonArray;
        do
        {
            if (sstream.peek() == ',')
                sstream.get();
            ja->insertItem(parseArrayItem(sstream));
            while (sstream.peek() != ',' && sstream.peek() != ']')
                sstream.get();
        } while (sstream.peek() != ']');
        sstream.get(); // 掠过']'
        JsonArrayItem *ans = new JsonArrayItem(ValueType::Array, ja);
        return ans;
    }
        // 数字
    default:
    {
        string temp;
        bool is_double = false;
        while (sstream.peek() == '+' || sstream.peek() == '-' || sstream.peek() == 'E' || sstream.peek() == 'e' || sstream.peek() == '.' || isdigit(sstream.peek()))
        {
            if (sstream.peek() == 'e' || sstream.peek() == 'E' || sstream.peek() == '.')
                is_double = true;
            temp.push_back(sstream.get());
        }
        JsonArrayItem *ans;
        if (is_double)
        {
            double *d = new double(stod(temp));
            ans = new JsonArrayItem(ValueType::Double, d);
        }
        else
        {
            int *i = new int(stoi(temp));
            ans = new JsonArrayItem(ValueType::Int, i);
        }
        return ans;
        break;
    }
    }
}

void JsonObject::parseObject(const char *file_name)
{
    ifstream f(file_name);
    stringstream sstream;
    sstream << f.rdbuf();

    while (sstream.peek() == ' ' || sstream.peek() == '\t' || sstream.peek() == '\n')
        sstream.get();
    sstream.get(); // 掠过'{'
    do
    {
        if (sstream.peek() == ',')
            sstream.get();
        this->insertItem(parseObjectItem(sstream));
        while (sstream.peek() != ',' && sstream.peek() != '}')
            sstream.get();
    } while (sstream.peek() != '}');
    while (sstream.peek() == ' ' || sstream.peek() == '\t' || sstream.peek() == '\n')
        sstream.get();
    sstream.get(); // 掠过'}'
}