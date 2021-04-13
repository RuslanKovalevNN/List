#include "List.h"

#include <gtest.h>


TEST(ListElem, can_create_element_in_list)
{
	ASSERT_NO_THROW(Node<int> e(4));
}


TEST(ListElem, can_get_data_of_element_in_list)
{
	TListElem<int> e(333);
	EXPECT_EQ(e.GetValue(), 333);
}

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(TList<int>());
}

TEST(List, can_copy_list)
{
	TList<int> a;
	a.InsLast(10);
	TList<int> b(a);
	EXPECT_EQ(10, b.GetLast()->GetData());
}

TEST(List, cannot_get_element_from_empty_list)
{
	TList<int> list;
	ASSERT_ANY_THROW(list.GetLast());
}

TEST(List, cannot_delete_element_from_empty_list)
{
	TList<int> list;
	ASSERT_ANY_THROW(list.DelLast());
}


TEST(List, can_insert_first_element)
{
	TList<int> f;
	ASSERT_NO_THROW(f.InsFirst(5));
}

TEST(List, can_insert_last_element)
{
	TList<int> list;
	ASSERT_NO_THROW(list.InsLast(5));
}

TEST(List, can_get_first_element)
{

	TList<int> list;
	int el1 = 21;
	int el2 = 5;
	int el3 = 7;
	int el4 = 3;
	list.InsFirst(el1);
	list.InsFirst(el2);
	list.InsFirst(el3);
	list.InsFirst(el4);
	EXPECT_EQ(3, list.GetFirst()->GetValue());
}

TEST(List, can_get_last_element)
{

	TList<int> list;
	int el1 = 3;
	int el2 = 2;
	int el3 = 13;
	list.InsFirst(el1);
	list.InsLast(el2);
	list.InsLast(el3);
	EXPECT_EQ(13, list.GetLast()->GetValue());
}

