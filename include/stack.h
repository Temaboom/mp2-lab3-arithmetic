// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class ValType>
class Stack
{
	ValType* p;
	int topindex;
	int size;
public:
	Stack(int s1 = 1000);
	~Stack();
	void push(ValType a);
	ValType pop();
	ValType top();
	bool isempty();
	void clean();
	int getquantity()
	{
		return topindex;
	}
	int getsize()
	{
		return size;
	}
};

template <class ValType>
Stack<ValType>::Stack(int s1)
{
	topindex = 0;
	size = s1;
	p = new ValType[s1];
}

template <class ValType>
Stack<ValType>::~Stack()
{
	delete[]p;
}

template <class ValType>
void Stack<ValType>::push(ValType a)
{
	if (topindex == size)
	{
		ValType* tmp = new ValType[size * 2];
		for (int i = 0; i < topindex; i++)
			tmp[i] = p[i];
		delete[] p;
		size = size * 2;
		p = new ValType[size];
		for (int i = 0; i < topindex; i++)
			p[i] = tmp[i];
	}
	p[topindex] = a;
	topindex += 1;
}

template <class ValType>
void Stack<ValType>::clean()
{
	topindex = 0;
}

template <class ValType>
bool Stack<ValType>::isempty()
{
	if (topindex == 0)
		return true;
	else
		return false;
}

template <class ValType>
ValType Stack<ValType>::pop()
{
	if (topindex == 0)
		throw ("Пустой стек");
	topindex -= 1;
	return p[topindex];
}

template <class ValType>
ValType Stack<ValType>::top()
{
	if (topindex == 0)
		throw ("Пустой стек");
	return p[topindex - 1];
}