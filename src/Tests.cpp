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

TEST(IteratorTest, ReverseIterator)
{
    LinkedList<int> linkedList;

    for(int i = 9; i >= 0; i--)
    {
        linkedList.add(i * 50);
    }

    int i = 0;
    for(auto it = linkedList.rbegin(); it != linkedList.rend(); it++, i++)
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

TEST(ClearTest, ClearTest)
{
    LinkedList<int> list1;

    for(int i = 10; i < 20; i++)
    {
        list1.add(i * 4);
    }

    list1.clear();

    EXPECT_EQ(list1.size(), 0);
}

TEST(GetTest, GetRandom)
{
    LinkedList<int> list1;

    for(int i = 10; i < 20; i++)
    {
        list1.add(i * 2);
    }

    EXPECT_EQ(list1.get(3), 26);
    EXPECT_EQ(list1.get(list1.size() - 1), 38);
    EXPECT_EQ(list1.get(0), 20);
    EXPECT_EQ(list1.get(5), 30);
    EXPECT_EQ(list1.get(8), 36);
}

TEST(GetTest, GetFirst)
{
    LinkedList<int> list1;

    list1.add(150);

    EXPECT_EQ(list1.get_first(), 150);

    list1.add(30);
    list1.add_last(79);
    list1.add(117);

    EXPECT_EQ(list1.get_first(), 150);

    list1.add_first(108);

    EXPECT_EQ(list1.get_first(), 108);
}

TEST(GetTest, GetLast)
{
    LinkedList<int> list1;

    list1.add(150);

    EXPECT_EQ(list1.get_last(), 150);

    list1.add(30);
    list1.add_last(79);
    list1.add(117);

    EXPECT_EQ(list1.get_last(), 117);

    list1.add_last(108);

    EXPECT_EQ(list1.get_last(), 108);
}

TEST(SearchingTest, FindTest)
{
    LinkedList<int> list1;

    for(int i = 10; i < 20; i++)
    {
        list1.add(i * 2);
    }

    EXPECT_EQ(list1.find(108), list1.end());
    EXPECT_EQ(*list1.find(20), 20);
    EXPECT_EQ(*list1.find(38), 38);
    EXPECT_EQ(*list1.find(32), 32);
}

TEST(SearchingTest, IndexOf)
{
    LinkedList<int> list1;

    for(int i = 5; i < 45; i++)
    {
        list1.add(i);
    }

    EXPECT_EQ(list1.index_of(5), 0);
    EXPECT_EQ(list1.index_of(44), list1.size() - 1);
    EXPECT_EQ(list1.index_of(45), -1);
    EXPECT_EQ(list1.index_of(-1503), -1);
    EXPECT_EQ(list1.index_of(32), 27);
}

TEST(ConvertingTest, ToArray)
{
    LinkedList<int> list1;

    for(int i = 0; i < 150; i++)
    {
        list1.add(i);
    }

    int* arr = list1.to_array();

    EXPECT_EQ(list1.get_first(), arr[0]);
    for(int i = 5; i < 10; i++)
    {
        EXPECT_EQ(list1.get(i), arr[i]);
    }
    EXPECT_EQ(list1.get_last(), arr[149]);
}

TEST(PollTest, Poll)
{
    LinkedList<int> list1;

    list1.add(120);
    list1.add(38);
    list1.add(196);
    list1.add(304);
    list1.add(12);

    EXPECT_TRUE(list1.poll() == 120 && list1.size() == 4);
    EXPECT_TRUE(list1.poll() == 38 && list1.size() == 3);
    EXPECT_TRUE(list1.poll() == 196 && list1.size() == 2);
    EXPECT_TRUE(list1.poll() == 304 && list1.size() == 1);
    EXPECT_TRUE(list1.poll() == 12 && list1.size() == 0);
}