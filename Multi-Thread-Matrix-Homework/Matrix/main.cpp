// ТВГУ ПМиК ФИиИТ 2024
// Андреев Семен Витальевич
#include "Matrix.h"
#include "Timer.h"

int main()
{
	srand(time(NULL));

	Matrix A(1000, 1000);
	Matrix B(1000, 1000);

	A.FillMatrix();
	B.FillMatrix();

	//std::cout << "Matrix A:" << std::endl << A;
	//std::cout << "Matrix B:" << std::endl << B;

	Timer t;
	Matrix C = A.SingleThreadMultiply(B);
	std::cout << "Single thread time:" << t.elapsed() << std::endl;

	t.reset();
	Matrix D = A.MultiThreadMultiply(B);
	std::cout << "Multi thread time:" << t.elapsed() << std::endl;


	//std::cout << "Matrix C:" << std::endl << C;
	//std::cout << "Matrix D:" << std::endl << D;

	return 0;
}