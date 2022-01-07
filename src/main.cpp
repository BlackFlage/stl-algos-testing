#include <iostream>
#include "LinkedList.h"

int main()
{
    LinkedList<int> list;

    list.add_first(69);
    list.add_first(169);
    list.add(100, 1);
    list.add(89, 2);

    {
        LinkedList<int> list2(list);
    }

    list.add(177);
}
