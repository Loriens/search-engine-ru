#include <iostream>
#include "head.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	boost::filesystem::path path;
	cin >> path;
	search_engine(path);

	cin.clear(); // Чистка от ошибок ввода
	cin.sync(); // Очищение буфера входных данных
	cin.get();
	return 0;
}