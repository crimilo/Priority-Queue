# Priority Queue

A priority queue implementation using a heap data structure.

Default behave as a max-heap, to use min-heap instead you can provide your own comparator class or `std::greater<>` from the standard library.

Example:

```cpp
#include "priority_queue.h"
#include <iostream>

int main()
{
   // Min-heap
   priority_queue<int, std::greater<int>> queue;

   queue.push(5);
   queue.push(3);
   queue.push(12);

   while (!queue.empty())
   {
      std::cout << queue.top() << '\n';
      queue.pop();
   }
}
```

## Installation
Include `priority_queue.h` in your .cpp file and you are ready to go!