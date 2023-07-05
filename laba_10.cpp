#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node *prev, *next;
    static Node* getnode(int data)
    {
        // Динамическое выделение памяти
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
};

class Deque {
public:
    Node* front;
    Node* rear;
    int Size;
public:
    Deque()
    {
        front = rear = NULL;
        Size = 0;
    }
    void insertFront(int data);
    void insertRear(int data);
    void deleteFront();
    void deleteRear();
    int find_min();
    void delete_min();
    int getFront();
    int getRear();
    int size();
    bool isEmpty();
    Node* getAt(int index) const;
    int operator[] (int index) const;
};

// Проверка на пустоту
bool Deque::isEmpty() { return (front == NULL); }

// Размер
int Deque::size() { return Size; }

// Вставить в начало
void Deque::insertFront(int data)
{
    Node* newNode = Node::getnode(data);
    if (newNode == NULL)
        cout << "OverFlow\n";
    else {
        if (front == NULL)
            rear = front = newNode;
        else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        Size++;
    }
}

// Вставить в конец
void Deque::insertRear(int data)
{
    Node* newNode = Node::getnode(data);
    if (newNode == NULL)
        cout << "OverFlow\n";
    else {
        if (rear == NULL)
            front = rear = newNode;
        else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        Size++;
    }
}

// Удаление первого
void Deque::deleteFront()
{
    if (isEmpty())
        cout << "Список пуст!\n";
    else {
        Node* temp = front;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        else
            front->prev = NULL;
        free(temp);
        Size--;
    }
}

// Удаление последнего
void Deque::deleteRear()
{
    if (isEmpty())
        cout << "Список пуст!\n";
    else {
        Node* temp = rear;
        rear = rear->prev;
        if (rear == NULL)
            front = NULL;
        else
            rear->next = NULL;
        free(temp);
        Size--;
    }
}

// Поиск минимального
int Deque::find_min() {
    Node* temp = front;
    int min = 1e5;
    while (temp != NULL) {
        if (temp->data < min) {
            min = temp->data;
        }
        temp = temp->next;
    }
    return min;
}

// Удалить минимальные элементы
void Deque::delete_min()
{
    if (isEmpty())
        cout << "Список пуст!\n";
    else {
        int min = find_min();
        Node* temp = front;
        while(temp != NULL) {
            if(temp->data == min) {
                if(temp->prev == NULL){
                    temp = temp->next;
                    deleteFront();
                }
                else if(temp->next == NULL){
                    deleteRear();
                }
                else {
                    Node* buff = temp;
                    temp = buff->prev;
                    temp->next = buff->next;
                    temp = buff->next;
                    temp->prev = buff->prev;
                    Size--;
                }
            }
            else
                temp = temp->next;
        }
    }
}

typedef void(*operation_ptr)(Node* Node);
// Функция преобразования
void tranformation(Node* Node){
    Node->data *= 2;
}

// Преобразовать все элементы
void transformation_all(Deque* Deque, operation_ptr func) {
    int i = 0;
    Node* Buff_Node = Deque->front;
    while(Buff_Node != NULL) {
        func(Buff_Node);
        Buff_Node = Buff_Node->next;
        i++;
    }
}

// Посмотреть на первый
int Deque::getFront()
{
    if (isEmpty())
        return -1;
    return front->data;
}

// Посмотреть на последний
int Deque::getRear()
{
    if (isEmpty())
        return -1;
    return rear->data;
}

// Выбор индекса
Node* Deque::getAt(int index) const {
    Node* newNode = Deque::front;
    int n = 0;
    while (n != index) {
        if (newNode == NULL)
            return newNode;
        newNode = newNode->next;
        n++;
    }
    return newNode;
}

// Оператор []
int Deque:: operator [] (int index) const {
    return getAt(index)->data;
}

void menu() {
    cout << "1 Добавить в начало\n";
    cout << "2 Добавить в конец\n";
    cout << "3 Удалить из начала\n";
    cout << "4 Удалить из конца\n";
    cout << "5 Удалить минимальные элементы\n";
    cout << "6 Посмотреть первый элемент\n";
    cout << "7 Посмотреть последний элемент\n";
    cout << "8 Посмотреть пустой ли список\n";
    cout << "9 Посмотреть весь список\n";
    cout << "10 Размер\n";
    cout << "0 Закончить программу\n";
}

int main()
{
    Deque dq;
    int number = 10;
    while (number != 0) {
        menu();
        cin >> number;
        switch (number)
        {
            case 1:
            {
                cout << "Какое число добавить?\n";
                int term;
                cin >> term;
                dq.insertFront(term);
                break;
            }
            case 2:
            {
                cout << "Какое число добавить?\n";
                int term;
                cin >> term;
                dq.insertRear(term);
                break;
            }
            case 3:
            {
                dq.deleteFront();
                break;
            }
            case 4:
            {
                dq.deleteRear();
                break;
            }
            case 5:
            {
                dq.delete_min();
                break;
            }
            case 6:
            {
                cout << "Первый элемент в очереди: " << dq.getFront() << '\n';
                break;
            }
            case 7:
            {
                cout << "Последний элемент в очереди: " << dq.getRear() << '\n';
                break;
            }
            case 8:
            {
                if (dq.isEmpty()) {
                    cout << "Список пуст!\n";
                }
                else {
                    cout << "Список не пуст!\n";
                }
                break;
            }
            case 9:
            {
                cout << "В списке такие элементы: ";
                for (int i = 0; i < dq.size(); ++i) {
                    cout << dq[i] << ' ';
                }
                break;
            }
            case 10:
            {
                cout << "В списке " << dq.size() << " элемента(-ов)\n";
                break;
            }
            case 0:
            {
                exit(0);
                break;
            }
        }
    }
    return 0;
}