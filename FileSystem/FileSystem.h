// ���� ���� ����� 2024
// ������� ����� ����������
#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <string>
#include <fstream>
struct File // ��������� ����
{
	std::string filename; // ��� �����
	std::string data;     // ���������� �����
	int size = 0;             // ������ �����
	bool is_open = false;         // ����, ��������� �� �������� �����
	std::mutex file_mutex;// ������� ��� ��������������� ������� � �����
	void OpenFile();
	void CloseFile();
};

class FileSystem // ����� �������� �������
{
	std::vector<File*> Files;// ������ ������ � �������
	int system_size;         // ���������� ������ � �������
	std::mutex sys_mutex;    // ������� ��� �������
public:
	FileSystem();
	FileSystem(const FileSystem& Object);
	~FileSystem();

	// ������� ����� ���� � �������� ������
	void FileCreate(const std::string& Name);
	// ������� ���������� ����� � �������
	void FileRead(const std::string& Name);
	// �������� ���������� � ����
	void FileWrite(const std::string& Name, const std::string& Data);
	// ������� ���� �� �������
	void FileDelete(const std::string& Name);
	// ������� ���������� � �������� �������
	void FileSystemInfo();
	// ����� ����� �� �����
	File* FileFindByName(const std::string& Name);
	// ����� ����� �� �����������
	File* FileFindByData(const std::string& Data);
	// ����� ����� � ������� ���������� � �������
	void FileFind(int MODE, const std::string& String);
	// ���������� ������ �� ����� � �������
	void CommandParser(const std::string& Filename);
};
