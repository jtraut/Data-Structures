#ifndef _ARRAY_BAG
#define _ARRAY_BAG

#include "BagInterface.h"
template<class ItemType>
class ArrayBag : public BagInterface<ItemType>
{
	private:
		static const int DEFAULT_CAPACITY = 25;
		ItemType items[DEFAULT_CAPACITY];
		int itemCount;
	
	public:
		ArrayBag();
		int getCurrentSize() const;
		int getCapacity() const;
		bool isEmpty() const;
		bool isFull() const;
		bool add(const ItemType& newItem);
		bool remove(const ItemType& anItem);
		void clear();
		bool contains(const ItemType& anItem) const;
		int getFrequencyOf(const ItemType& anItem) const;
		vector<ItemType> toVector() const;
};

#include "ArrayBag.cxx"
#endif
