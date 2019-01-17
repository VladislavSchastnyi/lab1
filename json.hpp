#pragma once

#include <any>
#include <iostream>
#include <string>

using namespace std;

class Json {
	// Обработанная строка, переданная в конструктор
	std::string saved_str;
	// Признак массив ли данный экземпляр
	bool this_array;
	any d;
public:
	// Конструктор из строки, содержащей Json-данные.
	Json(const std::string& s);

	// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
	bool is_array() const;
	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
	bool is_object() const;

	// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-массивом, генерируется исключение.
	std::any& operator[](const std::string& key);

	// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-объектом, генерируется исключение.
	std::any& operator[](int index);

	// Метод возвращает объект класса Json из строки, содержащей Json-данные.
	static Json parse(const std::string& s);

	// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
	static Json parseFile(const std::string& path_to_file);
};

/*Проверка корректности входной json-строки*/
bool check_json_str(const std::string & s) {
	//Считаем, что входная строка корректна с точки зрения формата json
	return true;
}

/*Проверка массив ли входная json-строка*/
bool check_array(const std::string & s) {
	//У json-массива последний символ ]
	if (s[s.size()] == ']') {
		//Поиск места первого включения ":[ в строку
		size_t key_end_pos = s.find("\":[");
		if (key_end_pos != -1) {
			return true;
		}
	}
	return false;
}

// Конструктор из строки, содержащей Json-данные.
Json::Json(const std::string & s) 
{
	//Проверка корректности входной строки
	if (check_json_str(s)) 
	{
		//Удаление знаков табуляции и перевода строки
		for (size_t i = s.find('"'); i < (s.size()); i++) 
		{
			if ((s[i] != 10) && (s[i] != 13) && (s[i] != 9)) 
			{
				//Удаление пробелов не внутри строк
				if ((s[i] != ' ')) 
				{
					saved_str.append(1, s[i]);
				}
			}
		}

		//Удаление последней закрывающей скобки
		saved_str.erase(saved_str.size() - 1, 1);

		for (size_t i = 0; i < (saved_str.size()); i++) 
		{
			std::cout << saved_str[i] ;
		}
		cout << std::endl;
		
		//std::cout << s.data() << std::endl;
		
		this_array = check_array(saved_str);
	}
	else 
	{
		throw std::runtime_error("Not valid input sring");
	}
}

// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
bool Json::is_array() const 
{
	return this_array;
}

// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
bool Json::is_object() const 
{
	return !this_array;
}

// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
// Если экземпляр является JSON-массивом, генерируется исключение.
std::any & Json::operator[](const std::string & key) {

	any result;

	if (this->is_object()) 
	{
		//Поиск ключа 
		size_t key_pos = this->saved_str.find("\"" + key +"\":");
		//size_t key_pos = this->saved_str.find(key);
		cout << "key " << key.data() << " find. Value pos " << key_pos << endl;
		if (key_pos != -1) 
		{
			switch (this->saved_str[key_pos + key.size()+3]) {
				case '{':
				{
					cout << "object" << endl;
					break;
				}			
			
				case '\"': 
				{
					cout << "string" << endl;
					//d = std::stod(&(this->saved_str[key_pos + key.size() + 3]), &key_pos);
					break;
				}
		    
				case 'n': 
				{
					cout << "ptr" << endl;
					break;
				}
			
				case 't':
				case 'f': 
				{
					cout << "bool" << endl;
					break;
				}
			
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					d=std::stod(&(this->saved_str[key_pos + key.size() + 3]), &key_pos);
					break;
				}
				default:
				{
					throw std::runtime_error("Invalid struct");
				}
			}
		}
		else 
		{
			throw std::runtime_error("Key not found");
		}
	}
	else 
	{
		throw std::runtime_error("Json is not a object");
	}
	return d;
}
