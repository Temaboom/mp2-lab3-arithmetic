// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "stack.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

enum Lextype {open_br, close_br, var, val, oper};

class Lexeme
{
	string s1;
	Lextype type;

public:
	Lexeme(){};
	string getstr()
	{
		return s1;
	}

	Lextype get_type()
	{
		return type;
	}

	Lexeme& operator=(const Lexeme & l);

	bool operator==(const Lexeme & l);

	void setlex(string s2)
	{
		s1 = s2;
	}
	void settype(Lextype t)
	{
		type = t;
	}
	int priority();
};

class Variable
{
	string name;
	double value;
public:
	Variable() {};
	string getname()
	{
		return name;
	}

	Variable& operator=(const Variable& v);

	void setvalue(double v) {
		value = v;
	};

	double getvalue()
	{
		return value;
	};

	void setname(string a)
	{
		name = a;
	}
};

class Arithmetic
{
	string s1;

	Lexeme* lexeme;
	int nLexem;

	Lexeme* polish;
	int nPolish;

	Variable* vars;
	int nVars;
public:
	Arithmetic(string str);
	int check();
	double calculate();
	void Polish();
	void set_vars();
	void print_polish();
	string print_polish_1();
};

string unary_minus(string s1);