// Определения функций, пространств имен и т.д.

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "head.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

void search_engine(boost::filesystem::path main_path, bool first_call) {	
	ofstream fileout; // Поток для вывода в файл

	if (first_call) {
		fileout.open("File JSON.txt", ios_base::out | ios_base::trunc); //(имя файла, открыть файл для записи и очистить его)
		fileout << "Path: " + main_path.string()
			<< endl
			<< endl;
	}
	else {
		fileout.open("File JSON.txt", ios_base::out | ios_base::app); // (имя файла, открыть файл для записи и добавлять в конец файла)
	}

	boost::filesystem::directory_iterator end_iter;
	for (boost::filesystem::directory_iterator der_iter(main_path); der_iter != end_iter; der_iter++) {
		if (boost::filesystem::exists(der_iter->path())) {
			if (boost::filesystem::is_regular_file(der_iter->path())) {
				ptree file; // Переменная формата JSON
				file.put("Path", der_iter->path().string()); // Метод put - добавление значения (название поля, значение поля)
				file.put("Name", der_iter->path().filename().string());
				file.put("Size", boost::filesystem::file_size(der_iter->path()));
				ostringstream buf;
				write_json(buf, file, false);
				string json = buf.str(); // Строка в формате JSON

				while (json.find("\\") + 1) { // Избавляемся от слэшэй экранирования символа заменой их на обратные слэши
					json.replace(json.find("\\"), 2, "/");
				}

				fileout << json // Выводим переменную в файл
					<< endl;
			}
			else if (boost::filesystem::is_directory(der_iter->path())) {
				fileout.close(); // Закрываем файл

				search_engine(der_iter->path(), false);

				fileout.open("File JSON.txt", ios_base::out | ios_base::app); // Открываем файл
			}
			else {
				cout << der_iter->path()
					<< " exists, but is neither a regular file or a directory\n";
			}
		}
		else {
			cout << der_iter->path() << "does not exist\n";
		}
	}

	fileout.close(); // Закрываем файл

	if (first_call) {
		cout << "Task has completed!"
			<< endl;
	}
}

/*
МОЖНО ДОРАБОТАТЬ:
- чтение файлов с русским названием (прогамма вместо русских букв выдаёт непонятные символы. Возможно, дело в кодировке).
*/