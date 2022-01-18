#include <iostream>
#include <list>

using namespace std;


template<typename T>
class Node
{
public:
	Node() {
		this->data = 0;
		this->p_next = nullptr;
	}

	Node(T data) {
		this->data = data;
	}

	Node(T new_data, Node* p_next) // конкретные данные и указатель на следующий объект
	{
		this->data = new_data;
		this->p_next = p_next;
	}

	~Node()
	{

	}

	int getData() // набор данных этого класса
	{
		return this->data;
	}

	Node* getNext() // позволяет получить доступ к данным
	{
		return this->p_next;
	}

	void display()
	{
		cout << "Data:" << getData();
	}

	void setData(T new_data)
	{
		this->data = new_data;
	}

	void setNext(Node* new_next)
	{
		this->p_next = new_next;
	}

private:
	T data;
	Node* p_next; // указатель для следующего элемента в списке
};

template<typename T>
class List {
public:
	List() {
		head = nullptr;
	}

	List(Node<T> head) {
		this->head = head;
	}

	bool isEmpty() // проверка пустой ли список
	{
		return head == nullptr;
	}

	Node<T>* getHeadPointer() {
		return head;
	}

	T getHead() {
		return head->getData();
	}

	List<T> getTail() {
		return List<T>(head->getNext());
	}

	void printGetTail() {
		Node<T>* p_last = head->getNext();
		while (p_last->getNext()) {
			cout << p_last->getData() << ",";
			p_last = p_last->getNext();
		}
		cout << p_last->getData();
	}

	void pushForward(T data)  // добавление в начало списка
	{
		head = new Node<T>(data, head);
	}

	void pushBack(T data)  // добавление в конец списка
	{
		Node<T>* p = new Node<T>(data);
		Node<T>* p_last = head;

		while (p_last->getNext()) {
			p_last = p_last->getNext();
		}

		p_last->setNext(p);
	}

	bool compare(List<T> other_list) {
		bool is_equal = true;
		Node<T>* p_this = head;
		Node<T>* p_other = other_list.getHeadPointer();

		while (p_this && p_other) {
			if (p_this->getData() != p_other->getData()) {
				is_equal = false;
				break;
			}

			p_this = p_this->getNext();
			p_other = p_other->getNext();
		}

		return is_equal;
	}

private:
	Node<T>* head;
};

int main() {
	setlocale(LC_ALL, "Russian");

	List<int> list = List<int>();
	list.pushForward(1);
	list.pushForward(5);
	list.pushForward(15);
	list.pushForward(2145);
	list.pushBack(20);
	cout << list.getHead() << "\n";
	list.printGetTail();

	cout << "\nЛист 2\n";

	List <int> this_list = List<int>();
	this_list.pushForward(1);
	this_list.pushForward(5);
	this_list.pushForward(15);
	this_list.pushForward(2145);
	this_list.pushBack(20);
	this_list.printGetTail();

	cout << "\nСравнение\n";
	cout << list.compare(this_list);

	return 0;
}