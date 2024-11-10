#ifndef CHILD_H_
#define CHILD_H_

#include <iostream>

using std::cout;
using std::ostream;
using std::istream;
using std::string;

class Child {

    public:

        // Constructor
        Child();
        Child(const Child &childToCopy);
        Child(string firstName, string lastName, int age);

        friend ostream& operator<<(ostream &stream, const Child &child);
        friend istream& operator>>(istream &stream, Child &child);

        bool operator<(const Child &toCompare) const;
        bool operator==(const Child &toCompare) const;
        bool operator!=(const Child &toCompare) const;

    private:
        string _firstName;
        string _lastName;
        int _age;

};




#endif