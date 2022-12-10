#pragma once

#include <functional>
#include <stdexcept>

template <
   class type,
   class compare = std::less<type>
>
class priority_queue
{
public:
   priority_queue(size_t capacity = 9) : m_heap(new type[capacity]), m_capacity(capacity), m_size(0)
   {
      if (capacity <= 1)
         throw std::runtime_error("Priority queue initial capacity must be > 1.");
   }

   /*
   * Constructs a heap from the given iterators.
   *
   * Time complexity: O(N log N)
   */
   template <class iterator>
   priority_queue(iterator first, iterator last) : m_capacity(last - first + 1), m_size(0)
   {
      if (m_capacity <= 1)
         throw std::runtime_error("Priority queue iterators difference must be >= 1.");

      m_heap = new type[m_capacity];

      while (first != last)
         m_heap[++m_size] = *(first)++;

      heapify();
   }

   priority_queue(const priority_queue& other) = default;

   priority_queue(priority_queue&& other) = default;

   ~priority_queue()
   {
      delete[] m_heap;
   }

   /*
   * Adds an element to the queue, and re-adjusts the queue order if needed.
   *
   * If the queue is full, a resize operation is attempted.
   *
   * Time complexity: Best case: O(1) - Worst case: O(log N).
   */
   void push(const type& value)
   {
      if (m_size == m_capacity - 1)
         double_capacity();

      m_heap[++m_size] = value;

      adjust_up(m_size);
   }

   /*
   * Returns the first element in the queue, i.e. the one with the highest priority.
   * 
   * If the queue is emtpy, the return value is undefined.
   * 
   * Time complexity: O(1).
   */
   const type& top() const noexcept
   {
      return m_heap[1];
   }

   /*
   * Removes the first element in the queue, and re-adjusts the queue order.
   *
   * Time complexity: O(log N).
   */
   void pop()
   {
      if (empty())
         return;

      m_heap[1] = m_heap[m_size--];

      adjust_down(1, 2, 3);
   }

   /*
   * Returns the number of current stored elements.
   */
   size_t size() const noexcept
   {
      return m_size;
   }

   /*
   * Returns whether the queue has no elements in it.
   */
   bool empty() const noexcept
   {
      return !m_size;
   }

private:
   type* m_heap;
   size_t m_capacity;
   size_t m_size;


   void double_capacity()
   {
      type* new_heap = new type[m_capacity * 2];
      m_capacity *= 2;

      for (size_t i = 1; i <= m_size; i++)
         new_heap[i] = m_heap[i];

      delete[] m_heap;
      m_heap = new_heap;
   }

   /*
   * Heapify (construct) a heap from an array (m_heap).
   * 
   * https://en.wikipedia.org/wiki/Binary_heap#Building_a_heap
   */
   void heapify()
   {
      for (size_t i = m_size / 2; i >= 1; i--)
         adjust_down(i, i * 2, i * 2 + 1);
   }

   void adjust_up(size_t node)
   {
      size_t parent = node / 2;

      while (parent > 0 && compare{}(m_heap[parent], m_heap[node]))
      {
         std::swap(m_heap[parent], m_heap[node]);
         node = parent;
         parent = parent / 2;
      }
   }

   void adjust_down(size_t parent, size_t left_child, size_t right_child)
   {
      while ((left_child <= m_size && compare{}(m_heap[parent], m_heap[left_child])) ||
            (right_child <= m_size && compare{}(m_heap[parent], m_heap[right_child])))
      {
         size_t children[] = {left_child, right_child};
         size_t greater_child = children[compare{}(m_heap[left_child], m_heap[right_child])];

         std::swap(m_heap[parent], m_heap[greater_child]);

         parent = greater_child;
         left_child = greater_child * 2;
         right_child = greater_child * 2 + 1;
      }
   }
};