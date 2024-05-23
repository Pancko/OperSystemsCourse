#include <iostream>
#include <thread>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

int user = 0;

HANDLE sem1 = CreateSemaphore(NULL, 0, 1, L"sem1");
HANDLE sem2 = CreateSemaphore(NULL, 0, 1, L"sem2");

static int OpUser()
{
	if (user == 1) return 2;
	else return 1;
}

void reader()
{
	string message;
	while (true) 
	{
		//check sem
		if (user == 1)
		{
			if (WaitForSingleObject(sem1, INFINITE) == WAIT_OBJECT_0)
			{
				fstream chat_file("Chat.txt");
				if (!chat_file.is_open())
				{
					cout << "Error: Chat file not opened";
					exit(-1);
				}
				chat_file >> message;
				cout << "User " << OpUser() << ": " << message << endl;
				chat_file.close();
			}
		}
		else
		{
			if (WaitForSingleObject(sem2, INFINITE) == WAIT_OBJECT_0)
			{
				fstream chat_file("Chat.txt");
				if (!chat_file.is_open())
				{
					cout << "Error: Chat file not opened";
					exit(-1);
				}
				chat_file >> message;
				cout << "User " << OpUser() << ": " << message << endl;
				chat_file.close();
			}
		}
	}
}

void writer() 
{
	string message;
	fstream chat_file;
	while (true) 
	{
		chat_file.open("Chat.txt");
		if (!chat_file.is_open())
		{
			cout << "Error: Chat file not opened";
			exit(-1);
		}
		cin >> message;
		if (message == "/stop")
		{
			chat_file.close();
			exit(0);
		}
		cout << "User " << user << ": " << message << endl;
		chat_file << message << "\n";
		chat_file.close();
		if (user == 1)
			ReleaseSemaphore(sem2, 1, NULL);
		else
			ReleaseSemaphore(sem1, 1, NULL);
	}
}


int main(int s, char** args) 
{
	user = atoi(args[1]);
	thread readThread(reader);
	thread writeThread(writer);

	readThread.join();
	writeThread.join();
}