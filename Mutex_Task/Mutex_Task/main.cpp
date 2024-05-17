#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

int i = 0;
int SIZE = 54321;

void visit(int *i_n)
{
	for (int j = 0; j < SIZE; j++)
		(*i_n)++;
}

void visit_mutex(int *i_n, std::mutex& mutex)
{
	mutex.lock();
	for (int j = 0; j < SIZE; j++)
		(*i_n)++;
	mutex.unlock();
}

void visit_atomic(std::atomic<int>* i_n)
{
	for (int j = 0; j < SIZE; j++)
		i_n->fetch_add(1);
}

int main()
{
	std::vector<std::thread> thread_vector;
	std::mutex mutex;
	int size = 1000;

	for (int j = 0; j < size; j++)
	{
		thread_vector.push_back(std::thread(visit, &i));
	}

	for (int j = 0; j < size; j++)
	{
		thread_vector[j].join();
	}
	std::cout << "Non-mutex version: " << i << std::endl;

	thread_vector.clear();
	i = 0;

	for (int j = 0; j < size; j++)
	{
		thread_vector.push_back(std::thread(visit_mutex, &i, std::ref(mutex)));
	}

	for (int j = 0; j < size; j++)
	{
		thread_vector[j].join();
	}
	std::cout << "Mutex version: " << i << std::endl;

	std::atomic<int> x = 0;
	thread_vector.clear();

	for (int j = 0; j < size; j++)
	{
		thread_vector.push_back(std::thread(visit_atomic, &x));
	}

	for (int j = 0; j < size; j++)
	{
		thread_vector[j].join();
	}
	std::cout << "Atomic version: " << x << std::endl;
	return 0;
}