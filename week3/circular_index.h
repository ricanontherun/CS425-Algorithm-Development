#ifndef CIRCULAR_INDEX_H
#define CIRCULAR_INDEX_H

struct CircularIndex
{
  std::size_t index;
  std::size_t size;

  CircularIndex(std::size_t size = 0)
    : index(0),
    size(size)
  {}

  CircularIndex & operator+=(std::size_t n)
  {
    this->add(n);

    return * this;
  }

  CircularIndex & operator++()
  {
    return (*this += 1);
  }

  private:
    void add(std::size_t n)
    {
      this->index = (this->index + n) % this->size;
    }
};

#endif
