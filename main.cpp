#include "JsonParser.h"
#include <iostream>

using namespace std;

int main()
{
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

    cout << her_json->getItemByName("crush?")->getJsonObjectItem().value()->getItemByName("do some for me")->getJsonArrayItem().value()->getItemByIndex(4)->getStringItem().value() << endl;

    her_json->dump("F:\\1大二下\\OOP\\test\\initial_test.txt");

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

    her_json->dump("F:\\1大二下\\OOP\\test\\add_test.txt");

    JsonObject *parsejson = new JsonObject;
    parsejson->parseObject("F:\\1大二下\\OOP\\test\\unformatted_parse_test.txt");

    parsejson->dump("F:\\1大二下\\OOP\\test\\formatted_print_test.txt");

    her_json->removeItem("her array is the same as mine ");
    her_json->insertString("this is a test for modify", "so that you can change the JsonObject variable by removing and inserting");

    her_json->dump("F:\\1大二下\\OOP\\test\\modify_test.txt");

    delete my_array;
    delete my_obj;
    delete her_json;
    delete body;
    delete her_array;
    delete her_virtue;
    delete parsejson;
}