#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/**
 * Implementation of functions listed
 * in LinkedList.h
 *
 * @author Kylun Robbins
 * @version 08/08/19
 */

/**
 * Default constructor that
 * sets head to null
 */
template <class T>
LinkedList<T> :: LinkedList()
{
    head = NULL;
}

/**
 * Copy constructor that sets current
 * LinkedList to argument
 *
 * @param copy  LinkedList to copy
 */
template <class T>
LinkedList<T> :: LinkedList(LinkedList<T> &copy)
{
    head = NULL;
    *this = copy;
}

/**
 * Deconstructor
 */
template <class T>
LinkedList<T> :: ~LinkedList()
{
    DeleteList();
}

/**
 * Builds a LinkedList by reading
 * from a file and storing the data into
 * Nodes
 *
 * @param fileName  File to open
 * @return bool     returns true if successful
 */
template <class T>
bool LinkedList<T> :: BuildList(string fileName)
{
    ifstream file;          // Declare a file
    file.open(fileName);    // Open argument file
    T item;                 // Object to store data
    T* pItem = &item;       // Pointer to object
    if(file)                // If the file is open
    {
        while(!file.eof())  // Keep going until file is empty
        {
            file >> item;   // Store data into item
            Insert(pItem);  // Insert into LinkedList
        }
    }
    file.close();           // Close file
    return true;
}

/**
 * Inserts the object argument into
 * the list at the correct position
 *
 * @param obj   Object to insert
 * @return bool True if inserted
 */
template <class T>
bool LinkedList<T> :: Insert(T *obj)
{
    if(obj == NULL)                 // If incoming object is null
    {
        return false;               // don't insert return false
    }

    Node* newNode;
    T newObj;

    newNode = new Node;             // Creates new node for insert
    newObj = *obj;                  // Stores copy of argument
    newNode -> data = newObj;       // Sets new node to hold argument

    if(head == NULL)                // If head is null
    {
        head = newNode;             // Insert at head
        head -> next = NULL;
        return true;
    }
    else if(newObj < head -> data)  // If obj is less than head
    {
        newNode -> next = head;     // Insert before head
        head = newNode;             // Set new node to head
        return true;
    }
    else
    {
        Node *current = head;           // Node to for traversal
        // While loop to find place to insert, if goes to end or data is larger than
        // the next element the loop stops
        while ((current->next != NULL) && (current -> next -> data <= newObj))
        {

            current = current->next;  // Keep traversing
        }

        if(current -> data == *obj)     // If current is equal to what is to be inserted
        {
            delete newNode;             // Delete newNode, no duplicates allowed
            return false;               // Return false, not inserted
        }

        newNode->next = current->next;  // Set new node's next
        current->next = newNode;        // Set previous node's next to current
        return true;
    }
}

/**
 * Removes the target element from
 * the LinkedList, and returns the data
 * of the element through reference
 *
 * @param target    Element to remove
 * @param result    Value of element removed
 * @return  bool    True if removed, false if not removed
 */
template <class T>
bool LinkedList<T> :: Remove(T target, T &result)
{
    Node* nodeDelete;
    if(head == NULL)                // If head is null
    {
        return false;               // List is empty, can't remove
    }

    if(head -> data == target)     // If target is head
    {
        nodeDelete = head;          // Set the node to delete to head
        head = head -> next;        // Set head now to next
        result = nodeDelete -> data;// Store data to return by reference
        free(nodeDelete);           // Delete head
        return true;
    }

    Node* current = head;           // Node for traversal
    // While loop to traverse area till the end or till the next node is the target
    while((current -> next != NULL) && ((current -> next -> data) != target))
    {
        current = current -> next;                      // Traverse
    }
    if(current -> next == NULL)                         // If the next node is null
    {
        return false;                                   // Didn't find target, return false
    }
    else                                                // Next node needs to be deleted
    {
        nodeDelete = current -> next;                   // Set nodeDelete pointer to next node
        current -> next = current -> next -> next;      // Link current to the next next node
        result = nodeDelete -> data;                    // Store data into result for return by reference
        free(nodeDelete);                               // Delete node
        return true;                                    // Success return true
    }
}

/**
 * Looks for the given target in the LinkedList
 * returns bool if the object is found and returns
 * the target through reference argument
 *
 * @param target    Object to look for
 * @param result    Reference to return value
 * @return bool     return true if object is in list
 */
template <class T>
bool LinkedList<T> :: Peek(T target, T &result) const
{
    if(head == NULL)                // If head is null
    {
        return false;               // List is empty, can't peek
    }

    if(head -> data == target)      // If target is head
    {
        result = head -> data;      // Set result to head's data
        return true;                // return true
    }

    Node* current = head;           // Node for traversal

    // While there is a next element and current is not the target
    while((current -> next != NULL) && ((current -> next -> data) != target))
    {
        current = current -> next;  // Keep traversing
    }

    if(current -> next == NULL)     // If there is no more elements
    {
        return false;               // target was not found, return false
    }
    else                                    // Else next element is target
    {
        result = current -> next -> data;   // Set result to next's data
        return true;                        // return true, target found
    }
}

/**
 * Checks to see if the current list
 * is empty
 *
 * @return bool true if empty, false if not empty
 */
template <class T>
bool LinkedList<T> :: isEmpty() const
{
    return this -> head == nullptr; // Return head is equal to null
}

/**
 * Deletes the current list
 */
template <class T>
void LinkedList<T> :: DeleteList()
{
    Node* temp;                 // Node pointer to hold nodes to delete
    while(head != NULL)
    {
        temp = head;            // Set temp to head
        head = head -> next;    // Traverse head to next
        free(temp);             // Delete temp(head)
    }
}

/**
 * Merges the instance LinkedList with
 * the argument LinkedList
 *
 * @param list1 List to merge
 * @return bool true if successful
 */
template <class T>
bool LinkedList<T> :: Merge(LinkedList &list1)
{
    if(this == &list1)       // Edge case: if list are equal
    {
        return true;        // Return true, do not need to merge
    }

    if(list1.head == NULL)  // Edge case: if argument list is empty
    {
        return false;       // Return false, can't merge
    }

    Node* current = list1.head;             // Node for traversal

    while(current != NULL)                  // While list still has elements
    {
        T retVal = current -> data;         // Store currents data into variable
        this -> Insert(&retVal);            // Insert data into original list
        current = current -> next;          // Traverse to next node
        list1.Remove(retVal, retVal);       // Remove previous node
    }
    return true;
}

/**
 * Helper method for testing,
 * prints current list
 */
template <class T>
void LinkedList<T> :: print()
{
    Node* current = this -> head;
    while(current != NULL)
    {
        cout << current -> data << endl;
        current = current -> next;
    }
}

/**
 * Overloads = operator, assigns the current LinkedList the
 * value of the argument LinkedList
 *
 * @param arg   List to assign to instance
 * @return      Updated LinkedList
 */
template <class T>
LinkedList<T>& LinkedList<T> :: operator=(const LinkedList<T> &arg)
{
    Node* current = arg.head;       // Node for traversal
    T retVal;                       // To store data
    T *pRetVal = &retVal;           // Pointer to Data

    this -> DeleteList();           // Clear the current list

    this -> head = NULL;            // Set current list's head to null

    while(current != NULL)          // While argument list has elements
    {
        retVal = current -> data;   // Store data
        this -> Insert(pRetVal);    // Insert data using pointer
        current = current -> next;  // Traverse
    }
    return *this;
}

/**
 * Overloads + operator, adds two lists together
 * to form a new third list, and returns it
 *
 * @param arg   List to add to instance
 * @return newList  result of addition
 */
template <class T>
const LinkedList<T>& LinkedList<T> :: operator+(const LinkedList<T> &arg)
{
    LinkedList<T>* newList = this;      // Create new linked list, assign it to this
    *newList += arg;                    // Add argument list to newList
    return *newList;                    // Return newList
}

/**
 * Adds a list to the current list. List
 * remains sorted.
 *
 * @param arg   List to add to instance
 * @return      Pointer to new list
 */
template <class T>
LinkedList<T>& LinkedList<T> :: operator+=(const LinkedList<T> &arg)
{
    Node* current = arg.head;               // Node for traversal
    T object;                               // Variable to keep track of data
    T *pointerToObject = &object;           // Pointer to data
    while(current != NULL)                  // While there is still elements
    {
        object = current -> data;           // Get data
        this -> Insert(pointerToObject);    // insert data to original list
        current = current -> next;          // Traverse
    }
    return *this;                           // Return new list
}

/**
 * Compares the current LinkedList to the argument
 * LinkedList and returns if equal of not
 *
 * @param obj   LinkedList to compare
 * @return bool true if equal, false if not equal
 */
template <class T>
bool LinkedList<T> :: operator==(const LinkedList<T> &arg) const
{
    Node* current = head;                       // Node pointer for traversal of instance
    Node* current2 = arg.head;                  // Node pointer for traversal of argument
    while(current != NULL)                      // While LinkedList still has data
    {
        if(current -> data != current2 -> data) // If instance data and argument data are not equal
        {
            return false;                       // return false, not equal
        }
        current = current -> next;              // Traverse instance
        current2 = current2 -> next;            // Traverse argument
    }
    return true;                                // If loop finishes then equal return true
}

/**
 * Compares the current LinkedList to the argument
 * LinkedList and returns bool representing if not
 * equal
 *
 * @param arg   LinkedList to compare
 * @return bool true if not equal, false if equal
 */
template <class T>
bool LinkedList<T> :: operator!=(const LinkedList<T> &arg) const
{
    Node* current = head;                       // Node pointer for traversal of instance
    Node* current2 = arg.head;                  // Node pointer for traversal of argument
    while(current != NULL)                      // While LinkedList still has data
    {
        if(current -> data != current2 -> data) // If instance data and argument data are not equal
        {
            return true;                        // return true, not equal
        }
        current = current -> next;              // Traverse instance
        current2 = current2 -> next;            // Traverse argument
    }
    return false;                               // If loop finishes then equal return false
}


