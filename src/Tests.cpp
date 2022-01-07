//
// Created by BlackFlage on 01.01.2022.
//
#include "gtest/gtest.h"
#include "LinkedList.h"

TEST(AddingTest, AddFirst)
{
    LinkedList<int> linkedList;

    linkedList.add_first(152);
    linkedList.add_first(169);
    linkedList.add_first(203);

    EXPECT_EQ(linkedList.size(), 3);
    EXPECT_EQ(linkedList.get(0), 203);
    EXPECT_EQ(linkedList.get(2), 152);
}

TEST(AddingTest, AddLast)
{
    LinkedList<int> linkedList;

    linkedList.add_last(152);
    linkedList.add_last(169);
    linkedList.add_last(203);

    EXPECT_EQ(linkedList.size(), 3);
    EXPECT_EQ(linkedList.get(0), 152);
    EXPECT_EQ(linkedList.get(2), 203);
}

TEST(AddingTest, AddBetween)
{
    LinkedList<int> linkedList;

    linkedList.add_first(150);
    linkedList.add_last(200);
    linkedList.add(175, 1);

    EXPECT_EQ(linkedList.size(), 3);
    EXPECT_EQ(linkedList.get(0), 150);
    EXPECT_EQ(linkedList.get(1), 175);
    EXPECT_EQ(linkedList.get(2), 200);
}

TEST(RemovingTest, RemoveFirst)
{
    LinkedList<int> linkedList;

    linkedList.add(150);

    EXPECT_EQ(linkedList.remove_first(), 150);
    EXPECT_EQ(linkedList.size(), 0);

    linkedList.add(200);
    linkedList.add(250);
    linkedList.add(300);

    EXPECT_EQ(linkedList.remove_first(), 200);
    EXPECT_EQ(linkedList.size(), 2);

    EXPECT_EQ(linkedList.remove_first(), 250);
    EXPECT_EQ(linkedList.size(), 1);

    EXPECT_EQ(linkedList.remove_first(), 300);
    EXPECT_EQ(linkedList.size(), 0);
}

TEST(RemovingTest, RemoveLast)
{
    LinkedList<int> linkedList;

    linkedList.add(150);

    EXPECT_EQ(linkedList.remove_last(), 150);
    EXPECT_EQ(linkedList.size(), 0);

    linkedList.add(200);
    linkedList.add(250);
    linkedList.add(300);

    EXPECT_EQ(linkedList.remove_last(), 300);
    EXPECT_EQ(linkedList.size(), 2);

    EXPECT_EQ(linkedList.remove_last(), 250);
    EXPECT_EQ(linkedList.size(), 1);

    EXPECT_EQ(linkedList.remove_last(), 200);
    EXPECT_EQ(linkedList.size(), 0);
}

TEST(RemovingTest, RemoveRandom)
{
    LinkedList<int> linkedList;

    linkedList.add(60);
    linkedList.add(80);
    linkedList.add(100);
    linkedList.add(120);
    linkedList.add(140);

    EXPECT_EQ(linkedList.remove(1), 80);
    EXPECT_EQ(linkedList.size(), 4);

    EXPECT_EQ(linkedList.remove(1), 100);
    EXPECT_EQ(linkedList.size(), 3);

    EXPECT_EQ(linkedList.remove(2), 140);
    EXPECT_EQ(linkedList.size(), 2);

    EXPECT_EQ(linkedList.remove(1), 120);
    EXPECT_EQ(linkedList.size(), 1);

    EXPECT_EQ(linkedList.remove(0), 60);
    EXPECT_EQ(linkedList.size(), 0);
}

TEST(IteratorTest, ForwardIterator)
{
    LinkedList<int> linkedList;

    for(int i = 0; i < 10; i++)
    {
        linkedList.add(i * 50);
    }

    int i = 1;
    for(auto it = linkedList.begin(); it != linkedList.end(); it++, i++)
    {
        *it = i * 1350;
        EXPECT_EQ(*it, i * 1350);
    }
}

TEST(IteratorTest, ConstForwardIterator)
{
    LinkedList<int> linkedList;

    for(int i = 0; i < 10; i++)
    {
        linkedList.add(i * 50);
    }

    int i = 0;
    for(auto it = linkedList.cbegin(); it != linkedList.cend(); it++, i++)
    {
        EXPECT_EQ(*it, i * 50);
    }
}

TEST(RuleOf5, CopyConstructor)
{
    LinkedList<int> list1;

    list1.add(15);

    LinkedList<int> list2(list1);

    ASSERT_EQ(list1.get(0), list2.get(0));

    for(int i = 2; i < 30; i++)
    {
        list1.add(i * 15);
    }

    LinkedList<int> list3(list1);
    ASSERT_EQ(list1.get(15), list3.get(15));
    ASSERT_EQ(list1.size(), list3.size());
}

TEST(RuleOf5, MoveConstructor)
{
    LinkedList<int> list1;

    for(int i = 0; i < 10; i++)
    {
        list1.add(i * 15);
    }

    LinkedList<int> list2(std::move(list1));

    EXPECT_EQ(list2.get(0), 0);
    EXPECT_EQ(list2.get(9), 135);
    EXPECT_EQ(list2.size(), 10);
    EXPECT_EQ(list1.size(), 0);
}

TEST(RuleOf5, AssignmentOperator)
{
    LinkedList<int> list1;

    for(int i = 0; i < 10; i++)
    {
        list1.add(i * 15);
    }

    LinkedList<int> list2 = std::move(list1);

    EXPECT_EQ(list2.get(0), 0);
    EXPECT_EQ(list2.get(9), 135);
    EXPECT_EQ(list2.size(), 10);
    EXPECT_EQ(list1.size(), 0);
}