#include "priority_queue.h"
#include <iostream>
#include <vector>

#define TEST_ASSERT(condition)                                      \
   if (!condition)                                                  \
   {                                                                \
      std::cerr << "test " << __FUNCTION__ << " failed! <<<\n";     \
      std::exit(-1);                                                \
   }                                                                \
   else                                                             \
   {                                                                \
      std::cout << "test " << __FUNCTION__ << " succeeded!\n";      \
   }                                                                \

void test0()
{
   priority_queue<int> queue;
   TEST_ASSERT(queue.size() == 0 && queue.empty());
}

void test1()
{
   priority_queue<int> queue;
   queue.push(1);
   TEST_ASSERT(queue.size() == 1 && !queue.empty());
}

void test2()
{
   priority_queue<int> queue;
   queue.push(1);
   queue.pop();
   TEST_ASSERT(queue.size() == 0 && queue.empty());
}

void test3()
{
   priority_queue<int> queue(2);
   queue.push(1);
   queue.push(2);
   queue.push(3);
   TEST_ASSERT(queue.size() == 2);
}

void test4()
{
   priority_queue<int> queue;
   queue.push(1);
   queue.push(2);
   queue.pop();
   TEST_ASSERT(queue.top() == 1);
}

void test5()
{
   priority_queue<int> queue;
   queue.push(2);
   queue.push(1);
   queue.pop();
   TEST_ASSERT(queue.top() == 1);
}

void test6()
{
   priority_queue<int> queue;
   queue.push(1);
   queue.push(2);
   queue.push(3);
   queue.push(4);
   queue.push(5);
   queue.push(6);
   TEST_ASSERT(queue.top() == 6);
}

void test7()
{
   priority_queue<int> queue;
   queue.push(2);
   queue.push(3);
   queue.push(4);
   queue.push(5);
   queue.push(6);
   queue.push(1);
   TEST_ASSERT(queue.top() == 6);
}

void test8()
{
   priority_queue<int> queue;
   queue.push(5);
   queue.push(3);
   queue.push(6);
   queue.push(4);
   queue.push(1);
   queue.push(2);
   queue.pop();
   queue.pop();
   TEST_ASSERT(queue.top() == 4);
}

void test9()
{
   priority_queue<int, std::greater<int>> queue;

   bool succeeded = true;

   queue.push(10);
   succeeded = succeeded && queue.top() == 10;
   queue.push(-10);
   succeeded = succeeded && queue.top() == -10;
   queue.push(20);
   succeeded = succeeded && queue.top() == -10;
   queue.push(-20);
   succeeded = succeeded && queue.top() == -20;
   queue.push(-30);
   succeeded = succeeded && queue.top() == -30;
   queue.push(-40);
   succeeded = succeeded && queue.top() == -40;
   queue.push(50);
   succeeded = succeeded && queue.top() == -40;

   TEST_ASSERT(succeeded);
}

void test10()
{
   priority_queue<int, std::greater<int>> queue;

   queue.push(5);
   queue.push(0);
   queue.push(10);
   queue.push(-5);
   queue.push(15);
   queue.push(10);
   queue.push(-10);
   queue.push(20);
   queue.push(30);
   queue.push(-30);

   bool succeeded = queue.size() == 10;

   succeeded = succeeded && queue.top() == -30; queue.pop();
   succeeded = succeeded && queue.top() == -10; queue.pop();
   succeeded = succeeded && queue.top() == -5; queue.pop();
   succeeded = succeeded && queue.top() == 0; queue.pop();
   succeeded = succeeded && queue.top() == 5; queue.pop();
   succeeded = succeeded && queue.top() == 10; queue.pop();
   succeeded = succeeded && queue.top() == 10; queue.pop();
   succeeded = succeeded && queue.top() == 15; queue.pop();
   succeeded = succeeded && queue.top() == 20; queue.pop();
   succeeded = succeeded && queue.top() == 30; queue.pop();

   succeeded = succeeded && queue.empty() && queue.size() == 0;

   TEST_ASSERT(succeeded);
}

void test11()
{
   std::vector<int> vector = {5, 3, 6, 4, 1, 2};
   priority_queue<int> queue(vector.begin(), vector.end());

   bool succeeded = queue.top() == 6; queue.pop();
   succeeded = succeeded && queue.top() == 5; queue.pop();
   succeeded = succeeded && queue.top() == 4; queue.pop();
   succeeded = succeeded && queue.top() == 3; queue.pop();
   succeeded = succeeded && queue.top() == 2; queue.pop();
   succeeded = succeeded && queue.top() == 1; queue.pop();

   TEST_ASSERT(succeeded);
}

int main()
{
   std::cout << "Running tests...\n";

   test0();
   test1();
   test2();
   test3();
   test4();
   test5();
   test6();
   test7();
   test8();
   test9();
   test10();
   test11();

   std::cout << "All tests have passed successfully!\n";
}