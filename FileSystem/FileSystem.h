// ТВГУ ПМиК ФИиИТ 2024
// Андреев Семен Витальевич
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
struct File // Структура Файл
{
	std::string filename; // Имя файла
	std::string data;     // Содержимое файла
	int size = 0;             // Размер файла
	bool is_open = false;         // Флаг, говорящий об открытии файла
	std::mutex file_mutex;// Мьютекс для единовременного доступа к файлу
	void OpenFile();
	void CloseFile();
};

class FileSystem // Класс файловой системы
{
	std::vector<File*> Files;// Вектор файлов в системе
	int system_size;         // Количество файлов в системе
	std::mutex sys_mutex;    // Мьютекс для системы
public:
	FileSystem();
	FileSystem(const FileSystem& Object);
	~FileSystem();

	// Создать новый файл с заданным именем
	void FileCreate(const std::string& Name);
	// Вывести содержимое файла в консоль
	void FileRead(const std::string& Name);
	// Записать информацию в файл
	void FileWrite(const std::string& Name, const std::string& Data);
	// Удалить файл из системы
	void FileDelete(const std::string& Name);
	// Вывести информацию о файловой системе
	void FileSystemInfo();
	// Поиск файла по имени
	File* FileFindByName(const std::string& Name);
	// Поиск файла по содержимому
	File* FileFindByData(const std::string& Data);
	// Поиск файла с выводом информации в консоль
	void FileFind(int MODE, const std::string& String);
	// Выполнение команд из файла в потоках
	void CommandParser(const std::string& Filename);
};
