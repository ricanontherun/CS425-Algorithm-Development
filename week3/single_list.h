#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <utility>

template <typename T>
class SingleList
{
  private:
    // Singly linked node.
    struct Node
    {
      // Default constructor.
      Node(const T & t = T{}, Node * next = nullptr)
        : data(t),
          next(next)
      {}

      // R-Value constructor
      Node(T && t, Node * next = nullptr)
        : data{ std::move( t ) }, next{ next }
      {}

      // The data the node holds.
      T data;

      // A pointer to the next node in the list.
      Node * next;
    }; // List::Node

    // Initialize the head/tail nodes.
    void init()
    {
      // Intialize with some empty nodes.
      this->head = new Node;
      this->tail = new Node;

      // Link them.
      this->head->next = this->tail;
    }

    Node * backNode()
    {
      Node * tmp = this->head;

      for ( ; tmp->next != this->tail; tmp = tmp->next ) ;

      return tmp;
    }

    // Head and tail nodes remove the need for special case operations.
    // Every node exists between these two.
    Node * head;
    Node * tail;

    // The length of the public section of the list (no head/tail)
    std::size_t length;
  public:
    // Default constructor
    SingleList()
      : head(nullptr),
        tail(nullptr),
        length(0)
    {
      this->init();
    }

    SingleList(const SingleList<T> & other)
      : SingleList()
    {
      for ( auto & x : other ) {
        this->push_back(x);
      }
    }

    SingleList & operator=(const SingleList<T> & rhs)
    {
      for ( auto & x : rhs ) {
        this->push_back(x);
      }

      return * this;
    }

    // Destructor
    ~SingleList()
    {
      // Clear the public nodes.
      this->clear();

      delete this->head;
      delete this->tail;
    }
    // Const Iterator
    class const_iterator
    {
      public:
        // default constructor.
        const_iterator()
          : current(nullptr)
        {}

        // Deference Operator, we return a const reference
        // because it's a CONST_iterator.
        T & operator*() const
        {
          return current->data;
        }

        // Increment operator.
        // Change the iterator to point to the next list item.
        const_iterator & operator++()
        {
          this->current = this->current->next;
          return *this;
        }

        const_iterator operator++ ( int )
        {
          const_iterator old = *this;
          ++( *this );
          return old;
        }


        // == operator, checks if the stored node is equal
        // to another node
        bool operator==(const const_iterator & rhs) const
        {
          return this->current == rhs.current;
        }

        // != operator, checks if the rhs is equal to this.
        bool operator!=(const const_iterator & rhs) const
        {
          // Although it's the natural choice, we can't use != here
          // because we're defining that operation
          // here. It would cause an infinite recursion. We to take the negation
          // of the == operator, something we've already defined above.
          return !(*this == rhs);
        }

      protected:
            Node * current;

            const_iterator(Node * current)
              : current(current)
            {}

            friend class SingleList<T>;
    }; // End SingleList::const_iterator

    const_iterator begin() const
    {
      return const_iterator{this->head->next};
    }

    const_iterator end() const
    {
      return const_iterator(this->tail);
    }

    // Get the list's size.
    std::size_t size() const
    {
      return this->length;
    }

    bool empty() const
    {
      return this->length == 0;
    }

    void clear()
    {
      while (!this->empty()) {
        this->pop_front();
      }
    }

    // Return reference to the front element.
    T & front()
    {
      // begin() always returns a reference to this->head->next
      return *(this->begin());
    }

    const T & front() const
    {
      return *(this->begin());
    }

    T & back()
    {
      return this->backNode()->data;
    }

    const T & back() const
    {
      return this->back();
    }

    // Insert an element at the front of the list.
    void push_front(const T & t)
    {
      this->insert(this->head, t);
    }

    void push_back(const T & t)
    {
      Node * back = this->backNode();

      ++this->length;

      back->next = new Node(t, back->next);
    }

    void pop_front()
    {
      if ( this->length == 0 ) {
        return;
      }

      Node * front = this->head->next;

      this->head->next = front->next;

      delete front;

      --this->length;
    }

    void pop_back()
    {
      if ( this->length == 0 ) {
        return;
      }

      Node * tmp = this->head;

      // Find the second to last node.
      for ( ; tmp->next->next != this->tail; tmp = tmp->next ) ;

      Node * back = tmp->next;

      tmp->next = back->next;

      delete back;

      --this->length;
    }

    // Insert t after it
    const_iterator insert(const_iterator it, const T & t)
    {
      Node * p = it.current;

      ++this->length;

      p->next = new Node(t, p->next);

      return const_iterator(p->next);
    }
}; // End List

#endif
