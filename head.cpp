// ����������� �������, ����������� ���� � �.�.

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "head.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::write_json;

void search_engine(boost::filesystem::path main_path, bool first_call) {	
	ofstream fileout; // ����� ��� ������ � ����

	if (first_call) {
		fileout.open("File JSON.txt", ios_base::out | ios_base::trunc); //(��� �����, ������� ���� ��� ������ � �������� ���)
		fileout << "Path: " + main_path.string()
			<< endl
			<< endl;
	}
	else {
		fileout.open("File JSON.txt", ios_base::out | ios_base::app); // (��� �����, ������� ���� ��� ������ � ��������� � ����� �����)
	}

	boost::filesystem::directory_iterator end_iter;
	for (boost::filesystem::directory_iterator der_iter(main_path); der_iter != end_iter; der_iter++) {
		if (boost::filesystem::exists(der_iter->path())) {
			if (boost::filesystem::is_regular_file(der_iter->path())) {
				ptree file; // ���������� ������� JSON
				file.put("Path", der_iter->path().string()); // ����� put - ���������� �������� (�������� ����, �������� ����)
				file.put("Name", der_iter->path().filename().string());
				file.put("Size", boost::filesystem::file_size(der_iter->path()));
				ostringstream buf;
				write_json(buf, file, false);
				string json = buf.str(); // ������ � ������� JSON

				while (json.find("\\") + 1) { // ����������� �� ������ ������������� ������� ������� �� �� �������� �����
					json.replace(json.find("\\"), 2, "/");
				}

				fileout << json // ������� ���������� � ����
					<< endl;
			}
			else if (boost::filesystem::is_directory(der_iter->path())) {
				fileout.close(); // ��������� ����

				search_engine(der_iter->path(), false);

				fileout.open("File JSON.txt", ios_base::out | ios_base::app); // ��������� ����
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

	fileout.close(); // ��������� ����

	if (first_call) {
		cout << "Task has completed!"
			<< endl;
	}
}

/*
����� ����������:
- ������ ������ � ������� ��������� (�������� ������ ������� ���� ����� ���������� �������. ��������, ���� � ���������).
*/