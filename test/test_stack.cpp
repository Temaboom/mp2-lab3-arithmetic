// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, stack_created)
{
	ASSERT_NO_THROW(Stack <int> a);
}

TEST(Stack, negative_length_stack)
{
	ASSERT_ANY_THROW(Stack <int> a(-10));
}

TEST(Stack, empty_stack)
{
	Stack<int> a(10);
	EXPECT_TRUE(a.isempty());
}