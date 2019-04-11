#include <iostream>
#include <ostream>
#include "List.h"


class vertex {

public:

    int x;
    int y;
    // vertex() = default;
    vertex(int x, int y) { this->x = x; this->y = y; }
    friend std::ostream& operator << (std::ostream& stream, const vertex& out) {
        stream << "(X: " << out.x;
        stream << ", Y: " << out.y << ")";
        return stream;
    }

};


int main() {

    List<vertex> myList;
    myList.PushBack(vertex(1, 1));
    myList.PushBack(vertex(2, 2));
    myList.PushFront(vertex(0, 0));
    myList.EmplaceBack(3, 3);


	for (auto iter = myList.begin(); iter != myList.end(); ++iter)
		std::cout << *iter << ", ";
	std::cout << std::endl;

    for (auto i = 0; i != myList.Len(); i++)
        std::cout << myList[i] << ", ";

    std::cout << std::endl;

    myList.PopBack();
    myList.PopFront();

    for (auto i = 0; i != myList.Len(); i++)
        std::cout << myList[i] << ", ";


    std::cout << std::endl << "Done!" << std::endl;
	system("pause");
    return EXIT_SUCCESS;
}