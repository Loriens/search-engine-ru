#include <iostream>
#include "head.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "������� ����� �������:"
		<< endl
		<< "1 - ��������� ����� � ��������"
		<< endl
		<< "2 - ������� ��������� � �������� (���� � �������� �������� � ������ ������ ����� \"File JSON.txt\", �������� � ����� � ����������)"
		<< endl;
	int choice;
	cin >> choice;
	cout << endl;
	if (choice == 1) {
		boost::filesystem::path path;
		cout << "����: ";
		cin >> path;
		search_engine(path);
	}
	else if (choice == 2) {
		search_changes();
	}

	cin.clear(); // ������ �� ������ �����
	cin.sync(); // �������� ������ ������� ������
	cin.get();
	return 0;
}