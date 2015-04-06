// ������� ��������, �������, �������, ����������� ���������� � �.�.

#ifndef HEAD_H_
#define HEAD_H_

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>

void search_engine(boost::filesystem::path path, bool first_call = true, std::string name_file = "File JSON.txt");
/* ������ ��� ����� � ����������� �� ������� ������. 
������� �� � ������� JSON � ���� "File JSON.txt", ������� � ����� � ������ ��������. */
std::string hash_sha1(const char * hash_str, int length);
/* ������� ���-����� ���������� ������. */
void search_changes(std::string name_file = "File JSON.txt");
/* ������� ��������� � �������� (���� � �������� �������� � ������ ������ ����� "File JSON.txt", �������� � ����� � ����������)*/

#endif HEAD_H_