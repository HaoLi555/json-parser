#include "JsonParser.h"
#include <iostream>

using namespace std;

int main()
{
    // 以下是一个可能的使用案例，包括的应用场景：
    // 1. 持久化储存程序运行中或者运行结果的一些变量
    // 2. 从指定文件中load，解析为JsonObject对象进而获取某些值

    // 使用方法如下，需要注意：
    // 1. 使用new创建JsonObject JsonArray对象
    // 2. 使用delete释放所有创建的JsonObject JsonArray对象

    JsonArray *my_array = new JsonArray;
    my_array->addBool(false);
    my_array->addDouble(542.5555);
    my_array->addInt(354353);
    my_array->addNull();
    my_array->addString("stay with me");

    JsonObject *my_obj = new JsonObject;
    my_obj->insertArray("do some for me", my_array);
    my_obj->insertBool("yeah?", true);
    my_obj->insertDouble("aaaaaa", 5.56);
    my_obj->insertInt("ak", 47);
    my_obj->insertNull("void");
    my_obj->insertString("name", "k.o.d.");

    JsonObject *her_json = new JsonObject;
    her_json->insertJson("crush?", my_obj);

    cout << "i want to say ";
    // 获取变量的示例
    cout << her_json->getItemByName("crush?")->getJsonObjectItem().value()->getItemByName("do some for me")->getJsonArrayItem().value()->getItemByIndex(4)->getStringItem().value() << endl;

    her_json->dump("F:\\1大二下\\OOP\\test\\initial_test.json");

    // --------------------------------------------------------------------------------------------------------
    her_json->insertBool("great", true);
    her_json->insertString("major", "CS");

    JsonObject *body = new JsonObject;
    body->insertInt("height", 165);
    body->insertDouble("weight", 55.5);

    her_json->insertJson("body", body);
    her_json->insertArray("her array is the same as mine ", my_array);

    JsonArray *her_array = new JsonArray;
    JsonObject *her_virtue = new JsonObject;
    her_virtue->insertBool("kind", true);
    her_virtue->insertBool("beautiful", true);
    her_virtue->insertBool("sweet", true);
    her_array->addJson(her_virtue);
    her_array->addString("caring");
    her_array->addString("luv");

    her_json->insertArray("why", her_array);

    her_json->dump("F:\\1大二下\\OOP\\test\\add_test.json");
    // ------------------------------------------------------------------------------------------------------------

    JsonObject *parsejson = new JsonObject;
    parsejson->parseObject("F:\\1大二下\\OOP\\test\\unformatted_parse_test.json");

    parsejson->dump("F:\\1大二下\\OOP\\test\\formatted_print_test.json");
    // -------------------------------------------------------------------------------------------------------------

    her_json->removeItem("her array is the same as mine ");
    her_json->insertString("this is a test for modify", "so that you can change the JsonObject variable by removing and inserting");
    her_array->removeItem(1);

    her_json->dump("F:\\1大二下\\OOP\\test\\modify_test.json");

    //---------------------------------------------------------------------------------------------------------------
    delete my_array;
    delete my_obj;
    delete her_json;
    delete body;
    delete her_array;
    delete her_virtue;
    delete parsejson;
}