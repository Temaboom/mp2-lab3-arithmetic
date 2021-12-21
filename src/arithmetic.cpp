// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"


string operations = "+*-/";
string openbrackets = "([";
string closebrackets = "])";
string squarebrackets = "[]";
string roundbrackets = "()";

Variable& Variable::operator = (const Variable& v)
{
	name = v.name;
	value = v.value;
	return *this;
}

Lexeme& Lexeme::operator = (const Lexeme& l)
{
	s1 = l.s1;
	type = l.type;
	return *this;
}

bool Lexeme::operator == (const Lexeme& l)
{
	if (l.type != type)
		return false;
	else
	{
		if (s1 != l.s1)
			return false;
		return true;
	}
}

int Lexeme::priority()
{
	int p;
	if (s1 == "(")
		p = 0;
	if ((s1 == "+") || (s1 == "-"))
		p = 1;
	if ((s1 == "*") || (s1 == "/"))
		p = 2;
	return p;
}

Arithmetic::Arithmetic(string str)
{
	s1 = str;
	size_t p, p1, p2, p3;
	lexeme = new Lexeme[s1.size()];
	vars = new Variable[10];
	nLexem = 0;
	nVars = 0;
	int nbr = 0;
	int i = 0;
	//разбиение на лексемы
	while (i < s1.size())
	{
		//открывающие скобки
		p1 = openbrackets.find(s1[i]);
		if (p1 != std::string::npos)
		{
			string opbrs;
			opbrs = s1[i];
			lexeme[nLexem].setlex(opbrs);
			lexeme[nLexem].settype(open_br);
			nLexem += 1;
			nbr += 1;
			i++;
			continue;
		}
		//закрывающие скобки
		p2 = closebrackets.find(s1[i]);
		if (p2 != std::string::npos)
		{
			string clbrs;
			clbrs = s1[i];
			lexeme[nLexem].setlex(clbrs);
			lexeme[nLexem].settype(close_br);
			nLexem += 1;
			nbr += 1;
			i++;
			continue;
		}
		//операции +*-/
		p3 = operations.find(s1[i]);
		if (p3 != std::string::npos)
		{
			string ops;
			ops = s1[i];
			lexeme[nLexem].setlex(ops);
			lexeme[nLexem].settype(oper);
			nLexem += 1;
			i++;
			continue;
		}
		//переменные
		if (isalpha(s1[i]) != 0)
		{
			nVars += 1;
			char a[10];
			string as;
			int j = 0;
			while ((i < s1.size()) && (isalpha(s1[i]) != 0))
			{
				a[j] = s1[i];
				j++;
				i++;
				if ((i < s1.size()) && (s1[i] == '['))
				{
					do
					{
						a[j] = s1[i];
						i++;
						j++;
					} while (s1[i] != ']');

					a[j] = s1[i];
					j++;
					i++;
				}

			}
			i--;
			as = a;
			as.erase(j);
			vars[nVars - 1].setname(as);
			lexeme[nLexem].setlex(as);
			lexeme[nLexem].settype(var);
			nLexem += 1;
			i++;
			continue;
		}
		//цифры
		if (isdigit(s1[i]) != 0)
		{
			char c[16];
			string cs;
			int j = 0;
			while ((isdigit(s1[i]) != 0) || (s1[i] == '.'))
			{
				c[j] = s1[i];
				j++;
				i++;
				if (i >= s1.size())
					break;
			}
			i--;
			cs = c;
			cs.erase(j);
			lexeme[nLexem].setlex(cs);
			lexeme[nLexem].settype(val);
			nLexem += 1;
			i++;
			continue;
		}
	}

	//создали поле для перевода в польскую
	polish = new Lexeme[nLexem - nbr];
	nPolish = 0;
}
int Arithmetic::check()
{
	//проверка числа скобочек
	size_t p1, p2, p3, p4, p5, p6;
	Stack <char> S(100);
	for (int i = 0; i < s1.length(); i++)
	{
		p1 = openbrackets.find(s1[i]);
		p2 = closebrackets.find(s1[i]);
		p3 = roundbrackets.find(s1[i]);
		p6 = squarebrackets.find(s1[i]);

		if (p1 != std::string::npos)
			S.push(s1[i]);
		else
		{
			if (p2 != std::string::npos)
			{
				if (S.isempty() == true)
				{
					throw "Нельзя перед открытием поставить закрывающуюся скобку";
					//					cout << "Нельзя перед открытием поставить закрывающуюся скобку";
					//					return 0;
				}

				p4 = roundbrackets.find(S.top());
				p5 = squarebrackets.find(S.top());

				if (!(((p3 != std::string::npos) && (p4 != std::string::npos)) || ((p5 != std::string::npos) && (p6 != std::string::npos))))
				{
					throw "Нельзя поставить закрывающуюся скобку";
					//					cout << "Нельзя поставить закрывающуюся скобку";
					//					return 0;
				}
				else
					S.pop();
			}
		}
	}

	for (int i = 0; i < s1.length(); i++)
	{
		if (i != (s1.length() - 1))
		{
			p1 = operations.find(s1[i]);
			p2 = operations.find(s1[i + 1]);

			//Проверка выражений "(+","(*","(/" 
			if ((s1[i] == '(') && (p2 != std::string::npos) && (s1[i + 1] != '-'))
			{
				throw "Ошибка выражений: (+,(*,(/";
				//				cout << "Ошибка выражений (+,(*,(/";
				//				return 0;
			}

			//Проверка выражений "-)","+)","/)","*)"
			if ((p1 != std::string::npos) && (s1[i + 1] == ')'))
			{
				throw "Ошибка выражений: -),+),/),*)";
				//				cout << "Ошибка выражений -),+),/),*)";
				//				return 0;
			}
		}

	}
	return 1;
}

void Arithmetic::Polish()
{
	Lexeme c;
	Lexeme x;
	Stack <Lexeme> st;
	int i = 0;
	while (i < nLexem)
	{
		c = lexeme[i];
		if ((c.get_type() == val) || (c.get_type() == var))
		{
			polish[nPolish] = c;
			nPolish += 1;
		}
		if (c.get_type() == open_br)
			st.push(c);
		if (c.get_type() == oper)
		{
			if (st.isempty())
				st.push(c);
			else
			{
				x = st.top();
				while (c.priority() <= x.priority())
				{
					x = st.pop();
					polish[nPolish] = x;
					nPolish += 1;
					if (!(st.isempty()))
						x = st.top();
					else break;
				}
				st.push(c);
			}
		}
		if (c.getstr() == ")")
		{
			x = st.pop();
			while (x.getstr() != "(")
			{
				polish[nPolish] = x;
				nPolish += 1;
				x = st.pop();
			}
		}
		i++;
	}
	while (!st.isempty())
	{
		x = st.pop();
		polish[nPolish] = x;
		nPolish += 1;
	}
}

double Arithmetic::calculate()
{
	Stack <double> st;
	double res;
	double x;
	int nvar = 0;
	for (int i = 0; i < nPolish; i++)
	{
		if (polish[i].get_type() == val)
		{
			x = atof(polish[i].getstr().c_str());
			st.push(x);
		}
		if (polish[i].get_type() == var)
		{
			x = vars[nvar].getvalue();
			st.push(x);
			nvar += 1;
		}
		if (polish[i].get_type() == oper)
		{
			double c, b = st.pop();
			double a = st.pop();
			if (polish[i].getstr() == "+")
				c = a + b;
			if (polish[i].getstr() == "-")
				c = a - b;
			if (polish[i].getstr() == "*")
				c = a * b;
			if (polish[i].getstr() == "/")
				c = a / b;
			st.push(c);
		}
	}
	res = st.pop();
	if (!st.isempty())
		throw "Ошибка";
	return res;
}

string unary_minus(string s1)
{
	size_t p;
	if (s1[0] == '-')
	{
		s1.insert(0, "0");
	}
	for (int i = 1; i < s1.length(); i++)
	{
		p = openbrackets.find(s1[i - 1]);
		if ((s1[i] == '-') && (p != std::string::npos))
		{
			s1.insert(i, "0");
		}
	}
	return s1;
}

void Arithmetic::set_vars()
{
	bool f = true;
	double tmp;
	for (int i = 0; i < nVars; i++) {
		f = true;
		for (int j = 0; (j < i) && (f); j++)
		{
			if (vars[i].getname() == vars[j].getname())
			{
				vars[i].setvalue(vars[j].getvalue());
				f = false;
			}
		}
		if (f)
		{
			string str = vars[i].getname();
			cout << "Введите значение: " << str << endl;
			cin >> tmp;
			vars[i].setvalue(tmp);
		}
	}
}

void Arithmetic::print_polish()
{
	for (int i = 0; i < nPolish; i++)
		cout << polish[i].getstr() << "\n";
}

string Arithmetic::print_polish_1()
{
	string s1;
	for (int i = 0; i < nPolish; i++)
		s1 += polish[i].getstr();
	return s1;
}