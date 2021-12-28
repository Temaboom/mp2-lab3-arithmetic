// реализация пользовательского приложения

#include "arithmetic.h"
#include <string>

int main()
{
	setlocale(LC_CTYPE, "Russian");
	string s1;
	int f;
	cout << "Input the value ";
	getline(cin, s1);
	s1 = unary_minus(s1);
	Arithmetic Exp(s1);
	f = Exp.check();
	Arithmetic Arr(s1);

	Arr.Polish();
	Arr.print_polish();
	Arr.set_vars();

	double res = Arr.calculate();
	cout << res;
	return 0;
}
