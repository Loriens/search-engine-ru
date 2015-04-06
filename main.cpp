#include <iostream>
#include "head.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "Введите номер команды:"
		<< endl
		<< "1 - прочитать файлы в каталоге"
		<< endl
		<< "2 - вывести изменения в каталоге (путь к каталогу хранится в первой строке файла \"File JSON.txt\", лежащего в папке с программой)"
		<< endl;
	int choice;
	cin >> choice;
	cout << endl;
	if (choice == 1) {
		boost::filesystem::path path;
		cout << "Путь: ";
		cin >> path;
		search_engine(path);
	}
	else if (choice == 2) {
		search_changes();
	}

	cin.clear(); // Чистка от ошибок ввода
	cin.sync(); // Очищение буфера входных данных
	cin.get();
	return 0;
}