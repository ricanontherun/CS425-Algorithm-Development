#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

template <typename Comparable>
class BinaryHeap
{
	public:
		explicit BinaryHeap(std::size_t capacity = 100)
			: array(capacity),
				currentSize(0)
		{}

		explicit BinaryHeap(const std::vector<Comparable> & items)
			: array(items.size() + 10),
				currentSize(items.size())
		{
			for ( int i = 0; i < items.size(); ++i ) {
				this->array[i + 1] = items[i]; // Leave room for array[0]
			}

			this->buildHeap();
		}

		bool isEmpty() const
		{
			return this->currentSize == 0;
		}

		// The heap-order property states that for any node, with the exception of the root, the key of it's parent node
		// must be smaller than the node's key. The root has no parent node, so this doesn't apply. This definition means
		// that the smallest node is the root.
		const Comparable & findMin() const
		{
			if ( this->isEmpty() ) {
				throw "Empty!";
			}

			return this->array[1];
		}

		void insert(const Comparable & x)
		{
			// Check if we need to resize.
			std::size_t array_size = this->array.size();
			if ( this->currentSize == array_size - 1 ) {
				this->array.resize(array_size * 2);
			}

			std::size_t hole = ++this->currentSize;
			Comparable copy = x;

			this->array[0] = std::move(copy);

			// As long as the parent node (hole / 2) is greater than the inserting element,
			// percolate the inserting element up by moving the parent element into the current position.
			// Basically keep swapping the hole and it's parent until we find a proper spot for it.
			for ( ; x < this->array[hole / 2]; hole /= 2 ) {
				this->array[hole] = std::move(this->array[hole / 2]);
			}

			this->array[hole] = std::move(array[0]);
		}

		void insert(Comparable && x)
		{
			std::size_t array_size = this->array.size();
			if ( this->currentSize == array_size - 1 ) {
				this->array.resize(array_size * 2);
			}

			std::size_t hole = ++this->currentSize;
			Comparable copy = std::move(x);

			this->array[0] = std::move(copy);

			// Percolate up. Starting at the current position, and using the left-child=2i rule, we check if the "parent" is
			// greater than x, if it is, we swap it with the current location.
			for ( ; x < this->array[hole / 2]; hole /= 2 ) {
				this->array[hole] = std::move(this->array[hole / 2]);
			}

			this->array[hole] = std::move(array[0]);
		}

		void deleteMin()
		{
			if ( this->isEmpty() ) {
				throw "Empty!";
			}

			this->array[1] = std::move(this->array[this->currentSize--]);
			this->percolateDown(1);
		}

		void deleteMin(Comparable & minItem);
		void makeEmpty();

		void print() const
		{
			for ( std::size_t i = 1; i < this->array.size(); ++i ) {
				std::cout << this->array.at(i) << "\n";
			}
		}

	private:
		std::size_t currentSize;
		std::vector<Comparable> array;

		void buildHeap()
		{
			for (int i = this->currentSize / 2; i > 0; --i) {
				this->percolateDown(i);
			}
		}

		void percolateDown(std::size_t hole)
		{
			std::size_t child;
			Comparable tmp = std::move(this->array[hole]);

			for ( ; hole * 2 <= this->currentSize; hole = child ) {
				child = hole * 2;

				if ( child != this->currentSize && this->array[child + 1] < this->array[child] ) {
					++child;
				}

				if ( this->array[child] < tmp ) {
					this->array[hole] = std::move(this->array[child]);
				} else {
					break;
				}
			}

			this->array[hole] = std::move(tmp);
		}
};

#endif
