//
// Created by BlackFlage on 01.01.2022.
//

#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(InsertingTest, InsertDifferent)
{
    LinkedList<int> linkedList;

    ASSERT_EQ(linkedList.size(), 0);

    linkedList.add_first(169);
    linkedList.append(34);
    linkedList.append(151);

    ASSERT_EQ(linkedList.size(), 3);

    linkedList.add_first(3342);

    ASSERT_EQ(linkedList.size(), 4);
}

TEST(GetTest, GetValues)
{
    LinkedList<int> linkedList;

    linkedList.add_first(69);
    linkedList.append(15);
    linkedList.append(25);

    ASSERT_EQ(linkedList.get(2), 25);

    linkedList.append(35);
    linkedList.append(45);
    linkedList.add_first(169);

    ASSERT_EQ(linkedList.get(0), 169);
    ASSERT_EQ(linkedList.get(5), 45);
}