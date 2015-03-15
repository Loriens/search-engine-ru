// Шаблоны структур, классов, функций, константных переменных и т.п.

#ifndef HEAD_H_
#define HEAD_H_

#include <boost/filesystem.hpp>
#include <fstream>

void search_engine(boost::filesystem::path path, bool first_call = true);
/* Читает все файлы и подкаталоги на наличие файлов. 
Выводит их в формате JSON в файл "File JSON.txt", лежащий в папке с данным проектом. */

#endif HEAD_H_