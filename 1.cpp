// Lab01.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "include\json.hpp"


const char * const json_data =
R"(
{
    "lastname" : "Ivanov",
    "firstname" : "Ivan",
    "age" : 25,
    "islegal" : false,
    "marks" : [
    	4,5,5,5,2,3
    ],
    "address" : {
    	"city" : "Moscow",
        "street" : "Vozdvijenka"
    }
})";
/*
R"(
{
"lastname" : "Ivanov",
"firstname" : "Ivan",
"age" : 25,
"islegal" : false,
"marks" : [
4,5,5,5,2,3
],
"address" : {
"city" : "Moscow",
"street" : "Vozdvijenka"
}
})";
*/

int main()
{
	std::string json;
	std::any a;

	Json object(json_data);
	//a = object["age"];

	//cout << std::any_cast<double> (a);
	cout << std::any_cast<double>(object["age"]);

	return 0;
}


 
