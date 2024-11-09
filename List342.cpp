#include "List342.h"
#include "Child.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template <class T>
List342<T>::List342() : _head(nullptr), _size(0){    }

template <class T>
List342<T>::List342(const List342 &listToCopy) : _head(nullptr), _size(0) { // we are copying listToCopy to this
    Node<T> *currNode = listToCopy._head; // This will be out iterator
    /* 
        We are asked to create a copy of data and not just point to the same object.
        If we simply do
        T objectCopy = *(currnode->data)
        
        We are not allocating new memory; it will be lost/forgotten outside of this function call
        
        T *objectCopy = new T(*(currNode->data));
        tells the computer to allocate new memory for this object (and remember it)
        Since we are doing 'new', we must remember to 'delete' later!
    */
    T *objectCopy = new T(*(currNode->data));
    Insert(objectCopy);
    currNode = currNode->next;
    while (currNode != nullptr) {
        T *objectCopy = new T(*(currNode->data));
        Insert(objectCopy);
        currNode = currNode->next;
    } // Frankly, this is inefficient...('Insert' must iterate thru whole list)
}

template <class T>
List342<T>::~List342() {
    DeleteList();
}

template <class T>
bool List342<T>::BuildList(string fileName) {
    return false;
}

template <class T>
bool List342<T>::Insert(T *object) {


    /* 
        PROBLEM:
        objectCopy was created INSIDE the function call, so it will
        NOT EXIST outside the function call!

        T objectCopy = *object; // Dereference
        T *objectCopyPointer = &objectCopy; // Create new pointer
       
        WHAT YOU DID WRONG:
        What you are supposed to do is to add a new NODE!!! into the LinkedList! You did not 
        create a new Node!! You only created a new object!!!
    */

    Node<T> *toInsert = new Node<T>; // Follow this structure when creating new Nodes; *create NEW* Node object, then manually add data
    T *copyOfObject = new T(*object); // Copy constructor invoked, 'copyOfObject' is instantiated as a pointer to the new object
    toInsert->data = copyOfObject; // Create a copy of the object, then set data to a pointer to the copy (project guidelines)

    if (_head == nullptr) { // Empty list
        _head = toInsert;
    } else if (*(toInsert->data) == *(_head->data)) {
        return false;
    } else if (*(toInsert->data) < *(_head->data)) { // If insert needs to happen first || Data is a pointer, so dereference it
            toInsert->next = _head;
            _head = toInsert;
    } else {
        
        Node<T> *checkPointer = _head;

        while (checkPointer->next != nullptr) { // Iterate thru list
            if (*(toInsert->data) == *(checkPointer->next->data)) {
                return false;
            } else if (*(toInsert->data) < *(checkPointer->next->data)) { // If the next value is bigger, we know where to insert
                break;
            }
            // checkPointer++; WRONG!! This is NOT a contiguous block of memory!! Not an array!
            checkPointer = checkPointer->next;
        }
        
        // Adding the object toInsert points to in the list
        toInsert->next = checkPointer->next;
        checkPointer->next = toInsert;
    }
    _size++;
    return true;
}

template <class T>
bool List342<T>::Remove(T target, T &result) {

    if (_head == nullptr) {
        return false;
    } else if (*(_head->data) == target) { // data is a pointer
        result = *(_head->data); // Make sure Child class has this overload
        Node<T> *temp = _head;
        T *tempData= _head->data;
        _head = _head->next;
        
        /* 
            We do NOT need to 'delete' *data. Why?

            'delete' only applies to objects that were created with keyword 'new'.
            In our case, Nodes are created with new (see Insert() method), but not 'data'. 
        */
       /*
            Now we do need to 'delete' *data, since we must create 'new' T(...) to copy object
        */
        
        delete temp; // To prevent memory leaks!
        delete tempData;
        _size--;
        return true;
    } else {
        Node<T> *checkPointer = _head;
        while (checkPointer->next->next != nullptr) {
            if (*(checkPointer->next->data) == target) { // data is a pointer
                result = *(checkPointer->next->data); // Make sure Child class has this overload
                Node<T> *temp = checkPointer->next; // Again, creating temp pointers so we can free up memory we no longer need
                T *tempData = checkPointer->next->data;
                checkPointer->next = checkPointer->next->next;
                delete temp;
                delete tempData;
                return true;
                _size--;
            }
            checkPointer = checkPointer->next;
        }
        if (*(checkPointer->next->data) == target) { // data is a pointer
            result = *(checkPointer->next->data); // Make sure Child class has this overload
            Node<T> *temp = checkPointer->next;
            T *tempData = checkPointer->next->data;
            checkPointer->next = checkPointer->next->next;
            delete temp;
            delete tempData;
            return true;
            _size--;
        } else {
            return false;
        }
    }
    return false;
}

template <class T>
bool List342<T>::Peek(T target, T &result) const {
        if (_head == nullptr) {
        return false;
    } else if (_head->next == nullptr) {
        if (*(_head->data) == target) { // data is a pointer
            result = target; // Make sure Child class has this overload
            return true;
        } else {
            return false;
        }
    } else {
        Node<T> *checkPointer = _head;
        while (checkPointer->next->next != nullptr) {
            if (*(checkPointer->next->data) == target) { // data is a pointer
                result = target; // Make sure Child class has this overload
                return true;
            }
            checkPointer = checkPointer->next;
        }
        if (*(checkPointer->next->data) == target) { // data is a pointer
            result = target; // Make sure Child class has this overload
            return true;
        } else {
            return false;
        }
    }
}

template <class T>
void List342<T>::DeleteList() {
    if (_head != nullptr) {
        while (_head != nullptr) {
            Node<T> *temp = _head;
            T *tempData = _head->data;
            _head = _head->next;
            delete temp;
            delete tempData;
            _size--;
        }
    }
}

template <class T>
bool List342<T>::Merge(List342 &listToMergeWith) {
    if (this != &listToMergeWith) { // 'this' is a pointer! *this is a dereference!
        while (listToMergeWith.Size()) {
            T *topItem = listToMergeWith._head->data;
            Insert(topItem);
            T temp;
            listToMergeWith.Remove(*(topItem), temp);
        }
        return true;
    }
    return false;
}

template <class T>
int List342<T>::Size() const {
    return _size;
}

template <class T>
List342<T> List342<T>::operator+(const List342 &list) const {
    List342<T> *toReturnPointer = new List342<T>();
    List342<T> toReturn = *toReturnPointer;

    toReturn = list;
    
    if (_head != nullptr) {
        Node<T> currPointer = _head;
        toReturn.Insert(currPointer->data);
        currPointer = currPointer->next;
        while (currPointer != nullptr) {
            toReturn.Insert(currPointer->data);
            currPointer = currPointer->next;            
        }
    }
    
    return toReturn;
}

template <class T>
List342<T> List342<T>::operator+=(const List342 &list) {
    if (list._head != nullptr) {
        Node<T> *currPointer = list._head;
        Insert(currPointer->data);
        currPointer = currPointer->next;
        while (currPointer != nullptr) {
            Insert(currPointer->data);
            currPointer = currPointer->next;            
        }
    }
    return *this;
}

template <class T>
bool List342<T>::operator==(const List342 &list) const {
    if (list.Size() == _size) {
        if (_head == nullptr) {
            return (list._head == nullptr);
        }
        Node<T> *thisListIterator = _head;
        Node<T> *listToCompateIterator = list._head;
        while (thisListIterator != nullptr) {
            if (*(thisListIterator->data) != *(listToCompateIterator->data)) {
                return false;
            }
            thisListIterator = thisListIterator->next;
            listToCompateIterator = listToCompateIterator->next;
        }
        return true;
    } else return false;
}

template <class T>
bool List342<T>::operator!=(const List342 &list) const {
        if (list.Size == _size) {
        if (_head == nullptr) {
            return (list._head != nullptr);
        }
        Node<T> *thisListIterator = _head;
        Node<T> *listToCompateIterator = list._head;
        while (thisListIterator != nullptr) {
            if (*(thisListIterator->data) != *(listToCompateIterator->data)) {
                return true;
            }
            thisListIterator = thisListIterator->next;
            listToCompateIterator = listToCompateIterator->next;
        }
        return false;
    } else return true;
}

template <class T>
List342<T> List342<T>::operator=(const List342 &list) { // we are copying 'list' to this
    if (list.Size()) {
        Node<T> *currPointer = list._head;
        T *currObjCopy = new T(*(currPointer->data));
        Insert(currObjCopy);
        currPointer = currPointer->next;
        while (currPointer != nullptr) {
            T *currObjCopy = new T(*(currPointer->data));
            Insert(currObjCopy);
            currPointer = currPointer->next;
        }
    }
    return *this; // return a reference (dereference pointer to a reference/object)
}

// template <class T>
// ostream& operator<<(ostream &stream, const List342<T> &list) {
//     Node<T> *currPointer = list._head;
//     while (currPointer != nullptr) {
//         stream << currPointer->data;
//         currPointer = currPointer->next;

//     }
//     return stream;
// }

int main() {

    Child c1("Angie", "Ham", 7), c2("Pradnya", "Dhala", 8),
    c3("Bill", "Vollmann", 13), c4("Cesar", "Ruiz", 6);
    Child c5("Piqi", "Tangi", 7), c6("Russell", "Wilson", 13),
    c7("Hank", "Aaron", 3), c8("Madison", "Fife", 7);
    Child c9("Miles", "Davis", 65), c10("John", "Zorn", 4), c11;
    List342<Child> class1, class2, soccer, chess;
    int a = 1, b = -1, c = 13;
    class1.Insert(&c1);
    class1.Insert(&c2);
    class1.Insert(&c3);
    class1.Insert(&c4);
    class1.Insert(&c5);
    class1.Insert(&c6);
    class1.Insert(&c5);
    cout << "class1: " << class1 << endl;
    if (! class1.Insert(&c1))
    {
    cout << "ERROR::: Duplicate" << endl;
    }
    class2.Insert(&c4);
    class2.Insert(&c5);
    class2.Insert(&c6);
    class2.Insert(&c7);
    class2.Insert(&c10);
    cout << "Class2: " << class2 << endl;
    class1.Merge(class2);
    class2.Merge(class1);
    class1.Merge(class2);
    class1.Merge(class1);
    cout << "class1 and 2 Merged: " << class1 << endl;
    class1.Remove(c4, c11);
    class1.Remove(c5, c11);
    class1.Remove(c11, c11);
    if (class1.Remove(c1, c11)) {
        cout << "Removed from class1, student " << c11 << endl;
    }
    cout << "class1: " << class1 << endl;
    class2 = class1;
    // class1.DeleteList();
    // cout << "class1: " << class1 << endl;
    // cout << "class2: " << class2 << endl;

    soccer.Insert(&c6);
    soccer.Insert(&c4);
    soccer.Insert(&c9);
    cout << "soccer: " << soccer << endl;
    soccer += class1;
    cout << "soccer += class1 : " << soccer << endl;
    List342<Child> football = soccer;
    if (football == soccer)
    {
    cout << "football: " << football << endl;
    }
    {
    if (football.Peek(c6, c11))
    cout << c11 << " is on the football team" << endl;
    }
    soccer.DeleteList();
    List342<int> numbers;
    numbers.Insert(&a);
    numbers.Insert(&b);
    numbers.Insert(&c);
    cout << "These are the numbers: " << numbers << endl;
    numbers.DeleteList();

    // cout << "ERROR::: Duplicate -> " << *(_head->data) << std::endl;

}

