#include <iostream>
#include <thread>
#include <Windows.h>
#include <fstream>
#include <string>

constexpr auto MSIZE = 10000;

using namespace std;

int user = 0;

HANDLE sem1 = CreateSemaphore(NULL, 0, 1, L"sem1");
HANDLE sem2 = CreateSemaphore(NULL, 0, 1, L"sem2");
HANDLE hFile = CreateFile(L"F:\\Projects\\VisualStudio\\OperSystemsCourse\\ThreadsChat\\x64\\Debug\\Chat2.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
HANDLE hMapFile;
char* shared_memory;

void reader()
{
	while (true)
	{
		//check sem
		if (user == 1)
		{
			if (WaitForSingleObject(sem1, INFINITE) == WAIT_OBJECT_0)
			{
				cout << "User 2: " << shared_memory << endl;
			}
		}
		else
		{
			if (WaitForSingleObject(sem2, INFINITE) == WAIT_OBJECT_0)
			{
				cout << "User 1: " << shared_memory << endl;
			}
		}
	}
}

void writer()
{
	while (true)
	{
		cin.getline(shared_memory, 1024);
		if (!strcmp(shared_memory, "/stop"))
			exit(0);
		cout << "User " << user << ": " << shared_memory << endl;
		if (user == 1)
			ReleaseSemaphore(sem2, 1, NULL);
		else
			ReleaseSemaphore(sem1, 1, NULL);
	}
}

int main(int s, char** args)
{
	user = atoi(args[1]);

	if (OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemory") == NULL) 
	{
		hFile = CreateFile(L"text.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, MSIZE, L"SharedMemory");
	}
	else 
	{
		hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemory");
	}
	shared_memory = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	thread readThread(reader);
	thread writeThread(writer);

	readThread.join();
	writeThread.join();
}