#include <iostream>
#include <string>
using namespace std;

/**
 *  Functions for a LinkedList that
 *  stores that is templatized to store
 *  different types of objects
 *
 *  @author Kylun Robbins
 *  @version 08/08/19
 */

template <class T>
class LinkedList
{

public:
    LinkedList<T>();
    LinkedList<T>(LinkedList<T> &copy);
    ~LinkedList<T>();

    bool BuildList(string fileName);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    bool isEmpty() const;
    void DeleteList();
    bool Merge(LinkedList &list1);

    LinkedList& operator =(const LinkedList<T> &arg);
    const LinkedList& operator +(const LinkedList<T> &arg);
    LinkedList& operator +=(const LinkedList<T> &arg);
    bool operator ==(const LinkedList<T> &arg) const;
    bool operator !=(const LinkedList<T> &arg) const;

    // << overload was not working in .cpp, but works in .h
    // Overloads << operator, prints all the nodes in the list
    friend ostream& operator<<(ostream &out, const LinkedList<T> &toPrint)
    {
        if (toPrint.head == NULL) {
            out << "Empty" << endl;
        } else {
            Node *current = toPrint.head;
            while (current != NULL) {
                out << current -> data;
                current = current->next;
            }
        }
        return (out);
    }

private:
    struct Node
    {
        T data;
        Node* next;
    };

    Node* head;

    void print();
};

#include "LinkedList.cpp"
