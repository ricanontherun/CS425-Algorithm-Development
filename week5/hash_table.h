#ifndef QUADRATIC_HASH_TABLE_H
#define QUADRATIC_HASH_TABLE_H

#include <vector>
#include <string.h>
#include <iostream>
#include <functional>

namespace HashTable
{

static bool IsPrime(int number)
{
	if (number == 2 || number == 3)
		return true;

	if (number % 2 == 0 || number % 3 == 0)
		return false;

	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= number)
	{
		if (number % (divisor - 1) == 0)
			return false;

		if (number % (divisor + 1) == 0)
			return false;

		divisor += 6;
	}

	return true;
}

static int nextPrime(int start)
{
	while ( !IsPrime(++start) ) {}

	return start;
}

class hash
{
	public:
		std::size_t operator()( const std::string & key )
		{
			std::size_t hashVal = 0;
			for( char ch : key )
				hashVal = 37 * hashVal + ch;
			return hashVal;
		}
};

template <typename T>
class Quadratic
{
	public:
		Quadratic(int size = 100)
			: array(size)
		{
			this->makeEmpty();
		}
		bool contains(const T & x) const
		{
			return this->isActive(this->findPos(x));
		}

		void makeEmpty()
		{
			this->currentSize = 0;

			for ( auto & entry : this->array ) {
				entry.info = EMPTY;
			}
		}

		bool insert(const T && x)
		{
			bool collision = false;
			int currentPos = this->findPos(x, &collision);

			if ( this->isActive(currentPos) ) {
				this->collision_cb();

				return false;
			}

			this->array[currentPos].element = std::move(x);
			this->array[currentPos].info = ACTIVE;

			if ( ++this->currentSize > (this->array.size() / 2) ) {
				this->rehash();
			}

			return true;
		}

		bool insert(const T & x)
		{
			bool collision = false;
			int currentPos = this->findPos(x, &collision);

			if ( this->isActive(currentPos) ) {
				this->collision_cb();
				return false;
			}

			this->array[currentPos].element = x;
			this->array[currentPos].info = ACTIVE;

			if ( ++this->currentSize > (this->array.size() / 2) ) {
				this->rehash();
			}

			return true;
		}

		bool remove(const T & x) const
		{
			int currentPos = this->findPos(x);

			// no need to delete, already deleted.
			if ( !this->isActive(currentPos) ) {
				return false;
			}

			this->array[currentPos].info = DELETED;
			return true;
		}

		void setCollisionCallback(std::function<void()> cb)
		{
			this->collision_cb = cb;
		}

		enum EntryType {ACTIVE, EMPTY, DELETED};

	private:
		struct HashEntry
		{
			T element;
			EntryType info;

			HashEntry(const T & e = T{}, EntryType i = EMPTY)
				: element(e),
					info(i)
			{}
		};

		bool isActive(int currentPos) const
		{
			return this->array[currentPos].info == ACTIVE;
		}

		int findPos(const T & x, bool * collision = nullptr) const
		{
			int offset = 1;

			// Compute the hash
			int currentPos = this->myhash(x);

			while ( this->array[currentPos].info != EMPTY && this->array[currentPos].element != x ) {
				currentPos += offset;
				offset += 2;

				if ( currentPos >= this->array.size() ) {
					currentPos -= this->array.size();
				}
			}

			return currentPos;
		}

		std::size_t myhash(const T & x) const
		{
			static hash f;
			return f(x) % this->array.size();
		}

		void rehash()
		{
			// Make a copy of the original table
			std::vector<HashEntry> oldArray = this->array;

			// Resize the current one, double the size and find the next prime size after that.
			this->array.resize(nextPrime(2 * oldArray.size()));

			// Invalidate the new array.
			for ( auto & entry : this->array ) {
				entry.info = EMPTY;
			}

			// Copy over the old array's elements.
			for ( auto & entry : oldArray ) {
				if ( entry.info == ACTIVE ) {
					// std::move allows us to avoid allocating new memory for the existing items.
					this->insert(std::move(entry.element));
				}
			}
		}

		std::vector<HashEntry> array;
		int currentSize;
		std::function<void()> collision_cb;
};

template <typename T>
class Linear
{
	public:
		Linear(int size = 100)
			: array(size)
		{
			this->makeEmpty();
		}
		bool contains(const T & x) const
		{
			return this->isActive(this->findPos(x));
		}

		void makeEmpty()
		{
			this->currentSize = 0;

			for ( auto & entry : this->array ) {
				entry.info = EMPTY;
			}
		}

		bool insert(const T && x)
		{
			bool collision = false;
			int currentPos = this->findPos(x, &collision);

			if ( this->isActive(currentPos) ) {
				this->collision_cb();
				return false;
			}

			this->array[currentPos].element = std::move(x);
			this->array[currentPos].info = ACTIVE;

			if ( ++this->currentSize > (this->array.size() / 2) ) {
				this->rehash();
			}

			return true;
		}

		bool insert(const T & x)
		{
			bool collision = false;
			int currentPos = this->findPos(x, &collision);

			if ( this->isActive(currentPos) ) {
				this->collision_cb();
				return false;
			}

			this->array[currentPos].element = x;
			this->array[currentPos].info = ACTIVE;

			if ( ++this->currentSize > (this->array.size() / 2) ) {
				this->rehash();
			}

			return true;
		}

		bool remove(const T & x) const
		{
			int currentPos = this->findPos(x);

			// no need to delete, already deleted.
			if ( !this->isActive(currentPos) ) {
				return false;
			}

			this->array[currentPos].info = DELETED;
			return true;
		}

		void setCollisionCallback(std::function<void()> cb)
		{
			this->collision_cb = cb;
		}

		enum EntryType {ACTIVE, EMPTY, DELETED};

	private:
		struct HashEntry
		{
			T element;
			EntryType info;

			HashEntry(const T & e = T{}, EntryType i = EMPTY)
				: element(e),
					info(i)
			{}
		};

		bool isActive(int currentPos) const
		{
			return this->array[currentPos].info == ACTIVE;
		}

		int findPos(const T & x, bool * collision = nullptr) const
		{
			int offset = 1;

			// Compute the hash
			int currentPos = this->myhash(x);

			while ( this->array[currentPos].info != EMPTY && this->array[currentPos].element != x ) {
				// Simple linear collision resolution strategy
				currentPos += 1;

				if ( currentPos >= this->array.size() ) {
					currentPos -= this->array.size();
				}
			}

			return currentPos;
		}

		std::size_t myhash(const T & x) const
		{
			static hash f;
			return f(x) % this->array.size();
		}

		void rehash()
		{
			// Make a copy of the original table
			std::vector<HashEntry> oldArray = this->array;

			// Resize the current one, double the size and find the next prime size after that.
			this->array.resize(nextPrime(2 * oldArray.size()));

			// Invalidate the new array.
			for ( auto & entry : this->array ) {
				entry.info = EMPTY;
			}

			// Copy over the old array's elements.
			for ( auto & entry : oldArray ) {
				if ( entry.info == ACTIVE ) {
					// std::move allows us to avoid allocating new memory for the existing items.
					this->insert(std::move(entry.element));
				}
			}
		}

		std::vector<HashEntry> array;
		int currentSize;
		std::function<void()> collision_cb;
};

}

#endif
