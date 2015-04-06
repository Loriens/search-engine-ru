// Шаблоны структур, классов, функций, константных переменных и т.п.

#ifndef HEAD_H_
#define HEAD_H_

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>

void search_engine(boost::filesystem::path path, bool first_call = true, std::string name_file = "File JSON.txt");
/* Читает все файлы и подкаталоги на наличие файлов. 
Выводит их в формате JSON в файл "File JSON.txt", лежащий в папке с данным проектом. */
std::string hash_sha1(const char * hash_str, int length);
/* Выводит хэш-сумму переданной строки. */
void search_changes(std::string name_file = "File JSON.txt");
/* Выводит изменения в каталоге (путь к каталогу хранится в первой строке файла "File JSON.txt", лежащего в папке с программой)*/

#endif HEAD_H_