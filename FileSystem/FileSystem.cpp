// ТВГУ ПМиК ФИиИТ 2024
// Андреев Семен Витальевич
#include "FileSystem.h"

FileSystem::FileSystem()
{
	system_size = 0;
}

FileSystem::FileSystem(const FileSystem& Object)
{
	Files = Object.Files;
	system_size = Object.system_size;
}

FileSystem::~FileSystem()
{
	for (File* i_file : Files)
	{
		delete i_file;
	}
	Files.clear();
	system_size = 0;
}

void FileSystem::FileCreate(const std::string& Name)
{
	sys_mutex.lock();
	std::cout << "Creating... \"" << Name << "\"" << std::endl;
	if (FileFindByName(Name) != nullptr)
	{
		std::cout << "File \"" << Name << "\" already exists!" << std::endl;
		sys_mutex.unlock();
		return;
	}
	File* new_file = new File;
	new_file->OpenFile();
	new_file->filename = Name;
	new_file->data = "";
	new_file->size = 0;
	new_file->CloseFile();
	Files.push_back(new_file);
	system_size++;
	sys_mutex.unlock();
}

void FileSystem::FileRead(const std::string& Name)
{
	sys_mutex.lock();
	std::cout << "Reading... \"" << Name << "\"" << std::endl;
	File* file = FileFindByName(Name);
	if (file == nullptr)
	{
		std::cout << "No such file named \"" << Name << "\"" << std::endl;
		sys_mutex.unlock();
		return;
	}
	while (file->is_open) {}
	file->OpenFile();
	std::cout << "Name: " << file->filename << std::endl;
	std::cout << "Size: " << file->size << std::endl;
	std::cout << "Data: " << file->data << std::endl;
	file->CloseFile();
	sys_mutex.unlock();
}

void FileSystem::FileWrite(const std::string& Name, const std::string& Data)
{
	sys_mutex.lock();
	std::cout << "Writing... \"" << Name << "\"" << std::endl;
	File* file = FileFindByName(Name);
	if (file == nullptr)
	{
		std::cout << "No such file named \"" << Name << "\"" << std::endl;
		sys_mutex.unlock();
		return;
	}
	while (file->is_open) {}
	file->OpenFile();
	file->data = Data;
	file->size = (int)Data.size();
	file->CloseFile();
	sys_mutex.unlock();
}

void FileSystem::FileDelete(const std::string& Name)
{
	sys_mutex.lock();
	std::cout << "Deleating... \"" << Name << "\"" << std::endl;
	File *file = FileFindByName(Name);
	if (file == nullptr)
	{
		std::cout << "No such file named \"" << Name << "\"" << std::endl;
		sys_mutex.unlock();
		return;
	}
	while (file->is_open) {}
	file->OpenFile();
	for (std::vector<File*>::iterator iterator = Files.begin(); iterator != Files.end(); iterator++)
	{
		if ((*iterator)->filename == Name)
		{
			Files.erase(iterator);
			file->CloseFile();
			delete file;
			system_size--;
			sys_mutex.unlock();
			return;
		}
	}
	if (file->is_open)
		file->CloseFile();
	sys_mutex.unlock();
}

void FileSystem::FileSystemInfo()
{
	sys_mutex.lock();
	std::cout << "FileSystem:" << std::endl;
	std::cout << "System size: " << system_size << std::endl;
	std::cout << "Files:" << std::endl;
	for (File* i_file : Files)
	{
		std::cout << "Name: " << i_file->filename << ", size = " << i_file->size << std::endl;
	}
	sys_mutex.unlock();
}

File* FileSystem::FileFindByName(const std::string& Name)
{
	for (File* i_file : Files)
	{
		if (i_file->filename == Name) 
		{
			return i_file;
		}
	}
	return nullptr;
}

File* FileSystem::FileFindByData(const std::string& Data)
{
	for (File* i_file : Files)
	{
		if (i_file->data == Data) 
		{
			return i_file;
		}
	}
	return nullptr;
}

void FileSystem::FileFind(int MODE, const std::string& String)
{
	sys_mutex.lock();
	std::cout << "Searching... \"" << String << "\"" << std::endl;
	File* temp_file = new File;
	switch (MODE)
	{
	case 0:
	{
		temp_file = FileFindByName(String);
		if (temp_file == nullptr)
		{
			std::cout << "File \"" << String << "\" not found!" << std::endl;
		}
		else
		{
			std::cout << "Name: " << temp_file->filename << ", size = " << temp_file->size << std::endl;
		}
		break;
	}
	case 1:
	{
		temp_file = FileFindByData(String);
		if (temp_file == nullptr)
		{
			std::cout << "File with data \"" << String << "\" not found!" << std::endl;
		}
		else
		{
			std::cout << "Name: " << temp_file->filename << ", size = " << temp_file->size << std::endl;
		}
		break;
	}
	}
	sys_mutex.unlock();
}

void FileSystem::CommandParser(const std::string& Filename)
{
	std::ifstream file(Filename);
	std::string temp_str;
	std::string temp_filename;
	std::string temp_data;
	std::vector<std::thread> vector_threads = {};
	if (file.is_open())
	{
		while (file >> temp_str)
		{
			if (temp_str == "create")
			{
				file >> temp_filename;
				vector_threads.push_back(std::thread(&FileSystem::FileCreate, this, temp_filename));
			}
			else if (temp_str == "delete")
			{
				file >> temp_filename;
				vector_threads.push_back(std::thread(&FileSystem::FileDelete, this, temp_filename));
			}
			else if (temp_str == "read")
			{
				file >> temp_filename;
				vector_threads.push_back(std::thread(&FileSystem::FileRead, this, temp_filename));
			}
			else if (temp_str == "write")
			{
				file >> temp_filename >> temp_data;
				vector_threads.push_back(std::thread(&FileSystem::FileWrite, this, temp_filename, temp_data));
			}
			else if (temp_str == "findname")
			{
				file >> temp_filename;
				vector_threads.push_back(std::thread(&FileSystem::FileFind, this, 0, temp_filename));
			}
			else if (temp_str == "finddata")
			{
				file >> temp_data;
				vector_threads.push_back(std::thread(&FileSystem::FileFind, this, 1, temp_data));
			}
			else if (temp_str == "systeminfo")
			{
				vector_threads.push_back(std::thread(&FileSystem::FileSystemInfo, this));
			}
		}
		for (std::thread& i_thread : vector_threads)
		{
			i_thread.join();
		}
	}
	else
	{
		std::cout << "Can't open commands file!";
		exit(-1);
	}
	file.close();
}

void File::OpenFile()
{
	is_open = true;
	file_mutex.lock();
}

void File::CloseFile()
{
	is_open = false;
	file_mutex.unlock();
}
