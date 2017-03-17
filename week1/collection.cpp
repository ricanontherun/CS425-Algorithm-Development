#include <iostream>
#include <array>
#include <stdexcept>
#include <iterator>

template <class T>
class Collection
{
  public:
    Collection(std::size_t size)
    : position(0), size(size)
    {
        this->storage = new T[this->size];
    }

    Collection(const Collection & rhs)
    : position(rhs.position), size(rhs.size), storage{nullptr}
    {
        this->storage = new T[this->size];

        for ( int i = 0; i < this->size; ++i ) {
            this->storage[i] = rhs.storage[i];
        }
    }

    ~Collection()
    {
      if ( this->storage )
      {
        delete [] this->storage;
      }
    }

    bool isEmpty() const
    {
      return this->size == 0;
    }

    void insert(T object)
    {
      this->validateSize();

      this->storage[this->position++] = object;
    }

    void remove(std::size_t index)
    {
      this->boundsCheck(index);
    }

    const T & operator[](std::size_t index) const
    {
      this->boundsCheck(index);

      return this->storage[index];
    }

  private:
    std::size_t position;
    std::size_t size;
    T * storage = nullptr;

    void validateSize()
    {
      if ( this->position >= size  )
      {
        // We double the size of the array.
        std::size_t new_size = this->size * 2;

        // Create a new temporary storage array of the new size.
        T * temp = new T[new_size];

        // Copy the contents of the old array to the temporary one.
        std::copy(this->storage, this->storage + this->size, temp);

        // Delete the original array.
        delete [] this->storage;

        // Setup new values for the size and storage.
        this->size = new_size;
        this->storage = temp;
      }
    }

    void boundsCheck(std::size_t index) const
    {
        if ( index > (this->size - 1) ) {
          throw std::out_of_range("error!!");
        }
    }
};

class Thing
{
  public:
    Thing() : x(0) {}
    Thing(int x) : x(x) {}
    int x;
};

int main()
{
  Collection<Thing> things(1);

  things.insert(Thing(100));
  things.insert(Thing(1234));

  const Thing & thing1 = things[0];
  const Thing & thing2 = things[1];

  std::cout << thing1.x << "\n";
  std::cout << thing2.x << "\n";

  Collection<Thing> thing_again(things);
}
