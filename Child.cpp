#include "Child.h"
#include <iostream>

using std::cout;
using std::ostream;

Child::Child() : _age(-1), _firstName(""), _lastName("") {  }

Child::Child(const Child &childToCopy) {
    _firstName = childToCopy._firstName;
    _lastName = childToCopy._lastName;
    _age = childToCopy._age;
}

Child::Child(string firstName, string lastName, int age) : _age(age), _firstName(firstName), _lastName(lastName) {  }

bool Child::operator<(const Child &toCompare) const {
    if (_lastName != toCompare._lastName) {
        return _lastName < toCompare._lastName;
    } else if (_firstName != toCompare._firstName) {
        return _firstName < toCompare._firstName;
    } else if (_age != toCompare._age) {
        return _age < toCompare._age;
    }

    return false;    
    
}

bool Child::operator==(const Child &toCompare) const {
    return ((_lastName == toCompare._lastName) && (_firstName == toCompare._firstName) && (_age == toCompare._age));
}

bool Child::operator!=(const Child &toCompare) const {
    return ((_lastName != toCompare._lastName) && (_firstName != toCompare._firstName) && (_age != toCompare._age));
}

ostream &operator<<(ostream &stream, const Child &child) {
    stream << child._firstName << child._lastName << child._age;
    return stream;
}
