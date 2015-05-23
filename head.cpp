// Определения функций, пространств имен и т.д.

#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "head.h"
#include "sha1.h"
#include "pbfile.pb.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

struct Fileinfo {
	std::string path;
	std::string hash;
	int size;
	std::string flag = "NEW";
};

void savepbuf(std::string filename, std::vector<Fileinfo> & vec_finfo) {
	nsofdir::ArrFilep flist;
	nsofdir::Filep * file_entry;
	std::ofstream output(filename, std::ofstream::binary);
	for (Fileinfo it : vec_finfo) {
		//Запись, просто по сделанным методам протобафа
		file_entry = flist.add_filep();
		file_entry->set_filepath(it.path);
		file_entry->set_size(it.size);
		file_entry->set_mdsixhash(it.hash);

	}
	//Вывод файла
	flist.PrintDebugString();
	//Записываем в output файл
	flist.SerializeToOstream(&output);
	output.close();
}

void search_engine(boost::filesystem::path main_path, bool first_call, string name_file) {	
	vector<Fileinfo> vec_list;
	if (boost::filesystem::exists(main_path)) {

		ofstream fileout; // Поток для вывода в файл

		if (first_call) {
			fileout.open(name_file, ios_base::out | ios_base::trunc); //(имя файла, открыть файл для записи и очистить его)
			fileout << main_path.string()
				<< endl
				<< endl;
		}
		else {
			fileout.open(name_file, ios_base::out | ios_base::in | ios_base::app); // (имя файла, открыть файл для записи и добавлять в конец файла)
		}

		boost::filesystem::directory_iterator end_iter;
		for (boost::filesystem::directory_iterator der_iter(main_path); der_iter != end_iter; der_iter++) {
			if (boost::filesystem::exists(der_iter->path())) {
				if (boost::filesystem::is_regular_file(der_iter->path())) {
					ifstream filein; // Поток для ввода из файла
					filein.open(der_iter->path().string(), ios_base::in); //(имя файла, открыть файл для чтения )
					
					string content; // Все данные из файла
					string buff;
					
					Fileinfo it;
					while (getline(filein, buff)) { // Читаем файл по строчке с помощью цикла
						content += buff;
					}

					filein.close(); // Закрываем файл

					ptree file; // Переменная формата JSON
					file.put("Path", der_iter->path().string()); // Метод put - добавление значения (название поля, значение поля)
					file.put("Name", der_iter->path().filename().string());
					file.put("Size", boost::filesystem::file_size(der_iter->path()));
					file.put("Hash", hash_sha1(content.c_str(), content.length()));
					it.path = der_iter->path().filename().string();
					it.size = boost::filesystem::file_size(der_iter->path()));
					it.hash = hash_sha1(content.c_str(), content.length()));
					vec_list.push_back(it)
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

					search_engine(der_iter->path(), false, name_file);

					fileout.open(name_file, ios_base::out | ios_base::in | ios_base::app); // Открываем файл
				}
				else {
					cout << der_iter->path()
						<< " exists, but is neither a regular file or a directory\n";
				}
			}
		}
		savepbuf("flist_copy.pbuf", vec_list)
		fileout.close(); // Закрываем файл

		if (first_call) {
			cout << "Задача завершена!"
				<< endl;
		}
	}
	else {
		cout << "does not exist\n";
	}
}

string hash_sha1(const char * hash_str, int length) {
	unsigned char * hash = new unsigned char[length];
	char * hexstring = new char [41]; // Строка хэш-суммы всегда одной длины
	sha1::calc(hash_str, length, hash);
	sha1::toHexString(hash, hexstring);

	return hexstring;
	delete[] hash;
	delete[] hexstring;
}

void search_changes(string name_file) {
	ifstream file_in; // Поток для ввода из файла
	file_in.open(name_file); // Открываем файл для чтения

	boost::filesystem::path main_path; // Путь к каталогу
	string str;
	vector<string> files_path; // Путь к файлам
	vector<string> files_hash; // Хэш файлов
	vector<string> files_path_copy;
	vector<string> files_hash_copy;

	getline(file_in, str);
	main_path = str;
	cout << "Проверяем файл "
		<< str
		<< endl;
	getline(file_in, str);
	while (getline(file_in, str)) { // Достаём значения из старой проверки каталога
		ptree pt;
		istringstream is(str);
		read_json(is, pt);
		string value;
		value = pt.get<string>("Path");
		files_path.push_back(value);
		value = pt.get<string>("Hash");
		files_hash.push_back(value);

		getline(file_in, str);
	}

	file_in.close(); // Закрываем файл. Очень важно!

	search_engine(main_path, 1, "File JSON copy.txt"); // Проводим новую проверку каталога
	file_in.open("File JSON copy.txt"); // Открываем файл для чтения

	getline(file_in, str);
	getline(file_in, str);
	while (getline(file_in, str)) { // Достаём значения из новой проверки каталога
		ptree pt;
		istringstream is(str);
		read_json(is, pt);
		string value;
		value = pt.get<string>("Path");
		files_path_copy.push_back(value);
		value = pt.get<string>("Hash");
		files_hash_copy.push_back(value);

		getline(file_in, str);
	}

	file_in.close(); // Закрываем файл. Очень важно!

	cout << endl
		<< endl
		<< "Изменились файлы: "
		<< endl;
	for (int i = 0; i < files_path.size(); i++) { // Проверяем все файлы на изменения
		for (int x = 0; x < files_path_copy.size(); x++) {
			if (files_path[i] == files_path_copy[x]) {
				if (files_hash[i] != files_hash_copy[x])
					cout << files_path[i]
					<< endl;
				files_path_copy[x] = "";
				files_path[i] = "";
			}
		}
	}
	cout << endl
		<< "Удалили файлы: "
		<< endl;
	for (int i = 0; i < files_path.size(); i++) {
		if (files_path[i] != "")
			cout << files_path[i]
			<< endl;
	}
	cout << endl
		<< "Новые файлы: "
		<< endl;
	for (int i = 0; i < files_path_copy.size(); i++) {
		if (files_path_copy[i] != "")
			cout << files_path_copy[i]
			<< endl;
	}
}

/*
МОЖНО ДОРАБОТАТЬ:
- чтение файлов с русским названием (прогамма вместо русских букв выдаёт непонятные символы. Возможно, дело в кодировке).
*/