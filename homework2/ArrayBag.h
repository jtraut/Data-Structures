#ifndef _ARRAY_BAG
#define _ARRAY_BAG

#include "BagInterface.h"
template<class ItemType>
class ArrayBag : public BagInterface<ItemType>
{
	private:
		static const int DEFAULT_CAPACITY = 4;
		ItemType* items; //array must be dynamic; so pointers are very yes
		int itemCount;
		int myCapacity; //added variable to track capacity
	
	public:
		ArrayBag(int capacity = DEFAULT_CAPACITY); // new constructor
		ArrayBag(const ArrayBag& anotherBag); // copy constructor
		~ArrayBag(); //destructor
		int getCurrentSize() const;
		int getCapacity() const;
		void resize(int newCapacity); // resize
		bool isEmpty() const;
		bool isFull() const;
		bool add(const ItemType& newEntry);
		bool remove(const ItemType& anEntry);
		void clear();
		bool contains(const ItemType& anEntry) const;
		int getFrequencyOf(const ItemType& anEntry) const;
		vector<ItemType> toVector() const;
		ArrayBag& operator=(const ArrayBag& anotherBag);
};

#include "ArrayBag.cxx"
#endif
