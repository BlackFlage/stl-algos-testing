#include <iostream>
#include "LinkedList.h"

int main()
{
    LinkedList<int> list;

    list.add_first(69);
    list.append(15);
    list.append(25);
    list.append(35);
    list.append(45);
    list.add_first(169);

    std::cout << "Pos 4: " << list.get(4) << '\n';
    std::cout << "Pos 5: " << list.get(5) << '\n';
}
