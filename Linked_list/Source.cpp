#include <iostream>

/*
		ДОМАШНЕЕ ЗАДАНИЕ:
		Реализуйте следующие методы для списка:
		+ pop_front() уничтожает первый элемент
		+ clear() очищает список
		+ empty() возвращает true если список пуст и false в противном случае
		+ swap(other_list) обменивает два списка значениями
		+ reverse() меняет последовательность элементов на обратную
		+ insert_after(value, position) добавляет элемент со значением value после позиции которая указана в position
		+ конструктор копирования/перемещения (и соответствующие операторы)
		+ remove(position) удаляет элемент в позиции position
		+ деструктор
		+ back() возвращает ссылку на последний элемент
		+ push_back(element) добавляет элемент в конец списка
		+ pop_back() уничтожает последний элемент
		+ search(value) возвращает true если элемент со значением value есть в списке и false в противном случае
		+ take_front() возвращает копию первого элемента (и удаляет оригинал)
		+ take_back() возвращает копию последнего элемента (и удаляет оригинал)

		DOPOLNITELNO
		+ OBRAWENIYE PO INDEKSU

*/

template<typename T>
struct Node {
	Node* m_next = nullptr;
	T m_value;
	Node(const T& data) :m_value(data) {}
};

template<typename T>
class LinkedList
{
public:
	LinkedList() = default;
	
	void push_back(const T& data) {

		if (!m_Head) {
			m_Head = new Node<T>(data);
		}
		else {
			Node<T>* current = m_Head;
			while (current->m_next)
			{
				current = current->m_next;
			}
			current->m_next = new Node<T>(data);
		}
		m_size++;
	}

	bool search(const T& value)
	{
		Node<T>* current = m_Head;
		while (current->m_next)
		{
			if (current->m_value == value)return true;

			current = current->m_next;
		}
		return false;
	}

	T& front()const
	{
		return m_Head->m_value;
	}

	void pop_back()
	{
		remove_element(m_size - 1);
	}

	void pop_front()
	{
		Node<T>* tmp = m_Head;
		m_Head = m_Head->m_next;
		delete tmp;
		m_size--;
	}

	size_t getSize()const
	{
		return m_size;
	}

	void clear()
	{
		int count = m_size + 1;

		while (count--)pop_front();

	}

	LinkedList(LinkedList<T>&& other)
	{
		m_Head = other.m_Head;
		m_size = other.m_size;

		other.clear();
	}


	LinkedList(const LinkedList<T>& other)
	{
		Node<T>* tmp = other.m_Head;
		while (tmp)
		{
			push_back(tmp->m_value);
			tmp = tmp->m_next;
		}
		m_size = other.m_size;
	}


	LinkedList& operator=(const LinkedList<T>& other)
	{
		clear();
		Node<T>* tmp = other.m_Head;
		while (tmp)
		{
			push_back(tmp->m_value);
			tmp = tmp->m_next;
		}
		m_size = other.m_size;

		return *this;
	}

	LinkedList& operator=(LinkedList<T>&& other)
	{

		m_Head = other.m_Head;
		m_size = other.m_size;

		other.clear();

		return *this;
	}

	T& take_front()///????????????
	{
		Node<T>* tmpNode = m_Head;
		T tmp = tmpNode->m_value;
		m_Head = m_Head->m_next;
		delete tmpNode;
		m_size--;
		return tmp;

	}

	T& take_back()
	{
		Node<T>* current = m_Head;
		while (current->m_next)
		{
			current = current->m_next;
		}
		T tmp = current->m_value;
		pop_back();
		m_size--;
		return tmp;

	}

	T& back()const
	{
		Node<T>* current = m_Head;
		while (current->m_next)
		{
			current = current->m_next;
		}
		return current->m_value;
	}

	void swap(LinkedList<T>& other)
	{

		Node<T>* tmp = std::move(m_Head);
		m_Head = std::move(other.m_Head);
		other.m_Head = std::move(tmp);
	}

	T& operator[](const int index)
	{
		int count = 0;
		Node<T>* current = m_Head;
		while (current)
		{
			if (count == index)
			{
				return current->m_value;
			}
			current = current->m_next;
			count++;
		}
	}

	void remove_element(const int index)
	{
		if (index)
		{
			Node<T>* current = m_Head;

			for (int i = 0; i < index - 1; ++i)
				current = current->m_next;

			Node<T>* deleteTmp = current->m_next;
			current->m_next = deleteTmp->m_next;
			delete deleteTmp;
			m_size--;
		}
		else
		{
			pop_front();
		}
	}

	void insert_after(const T& value, const size_t position)
	{
		if (!position) {
			push_front(value);
		}
		else {
			Node<T>* current = m_Head;
			for (int i = 0; i < position; ++i)
				current = current->m_next;

			Node<T>* tmp = new Node<T>(value);
			Node<T>* next = current->m_next;
			current->m_next = tmp;
			tmp->m_next = next;
			m_size++;
		}
	}

	void reverse()
	{
		Node<T>* tmp = m_Head;
		int size = m_size;
		while (tmp) {
			push_front(tmp->m_value);
			tmp = tmp->m_next;
		}
		while (size) {
			pop_back();
			size--;
		}
	}

	void push_front(const T& element)
	{
		Node<T>* node = new Node<T>(element);
		node->m_next = m_Head;
		m_Head = node;
		m_size++;
	}

	bool empty()const
	{
		return m_Head;  // return m_size;
	}

	~LinkedList()
	{
		clear();
	}

private:
	friend std::ostream& operator << (std::ostream& os, const LinkedList& l)
	{
		Node<T>* current = l.m_Head;
		while (current)
		{
			os << current->m_value;

			if (current->m_next)os << " - ";

			current = current->m_next;
		}

		return os;
	}

	Node<T>* m_Head = nullptr;
	size_t m_size = 0;
};



int main()
{
	LinkedList<int> list;
	list.push_back(3);
	list.push_back(5);
	list.push_back(6);
	list.push_front(2);
	list.push_front(1);
	std::cout << "list              \t=\t" << list << '\n';
	std::cout << std::boolalpha << "list.empty()        \t=\t" << list.empty() << '\n';
	list.insert_after(9, 1);
	std::cout << "insert_after(9, 1)\t=\t";
	std::cout << list << '\n';

	std::cout << "list.search(5)    \t=\t" << list.search(5) << '\n';

	list.reverse();
	std::cout << "list.reverse()    \t=\t" << list << '\n';

	std::cout << "list.take_back()  \t=\t" << list.take_back() << '\n';

	std::cout << "list.take_front() \t=\t" << list.take_front() << '\n';

	list.pop_front();
	std::cout << "pop_front()       \t=\t";
	std::cout << list << '\n';

	list.pop_back();
	std::cout << "pop_back()        \t=\t";
	std::cout << list << '\n';

	list.remove_element(1);
	std::cout << "list.remove_element(1)\t=\t" << list << '\n';


	list.push_back(5);
	list.push_back(4);
	list.push_back(4);
	list.push_back(4);
	list.push_back(5);
	list.clear();
	std::cout << "clear()               \t=\t" << list;

}