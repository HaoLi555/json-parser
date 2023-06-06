#include"JsonParser.h"
#include<iostream>

using namespace std;

int main(){

    JsonArray array;
    array.addBool(false);
    array.addDouble(5.5454);
    array.addInt(123456);
    array.addNull();
    array.addString("what the fuck");
    JsonObject j;
    j.insertBool("great", true);
    j.insertArray("my array", &array);


    
}