// ������� ��������, �������, �������, ����������� ���������� � �.�.

#ifndef HEAD_H_
#define HEAD_H_

#include <boost/filesystem.hpp>
#include <fstream>

void search_engine(boost::filesystem::path path, bool first_call = true);
/* ������ ��� ����� � ����������� �� ������� ������. 
������� �� � ������� JSON � ���� "File JSON.txt", ������� � ����� � ������ ��������. */
std::string hash_sha1(const char * hash_str, int length);
/* ������� ���-����� ���������� ������. */

#endif HEAD_H_