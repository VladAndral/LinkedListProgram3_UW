#ifndef LIST342_H_
#define LIST342_H_

#include <iostream>

using std::cout;
using std::string;
using std::ostream;

/* 
        TODO: REMEMBER TO ADD .cpp CODE HERE!!!
 */

template<class T>
struct Node {
    T *data; // NOT raw data! A POINTER to data
    Node *next = nullptr;
};

template<class T>
class List342 {

    public:
        
        // Constructors
        List342();
        List342(const List342 &listToCopy);
        ~List342();

        // Action Verbs
        bool BuildList(string fileName);
        bool Insert(T *object);
        bool Remove(T target, T &result);
        bool Peek(T target, T &result) const;
        void DeleteList();
        bool Merge(List342 &listToMergeWith);

        // Gets n Sets
        int Size() const;

        // Operator Overloads
        List342 operator+(const List342 &list) const;
        List342 operator+=(const List342 &list);
        bool operator==(const List342 &list) const;
        bool operator!=(const List342 &list) const;

        List342 operator=(const List342 &list);

        /* 
            Since we are trying to operate on a templated function, the definition needs to be visible
         */
        friend ostream& operator<<(ostream &stream, const List342<T> &list) {
            Node<T> *currPointer = list._head;
            while (currPointer != nullptr) {
                stream << *(currPointer->data);
                currPointer = currPointer->next;

            }
            return stream;
        }



    private:
        int _size;
        Node<T> *_head;

};

#endif

