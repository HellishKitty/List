#ifndef LIST_LISTEXCEPTIONS_H
#define LIST_LISTEXCEPTIONS_H

#include <exception>

class ListException : std::exception {

    const char* what()  const noexcept override {
        return "List exception occurred!";
    }

};


class OutOfRangeException : ListException {

    const char* what()  const noexcept override {
        return "Index is out of range!";
    }

};

#endif //LIST_LISTEXCEPTIONS_H
