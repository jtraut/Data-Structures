//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>

template<class ItemType>
LinkedBag<ItemType>::LinkedBag()
{
	itemCount = 0;
	head_ptr = nullptr;
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
   Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
   
   if (origChainPtr == nullptr)
      head_ptr = nullptr;  // Original bag is empty
   else
   {
      // Copy first node
      head_ptr = new Node<ItemType>();
      head_ptr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      Node<ItemType>* newChainPtr = head_ptr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return (head_ptr == nullptr);
}  // end isEmpty

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anItem) const
{
	Node<ItemType>* curr = head_ptr;
	while (curr != nullptr)	
	{
		if (curr->getItem() == anItem)
			return true;
		else 
			curr = curr->getNext();
	}
	return false;
}  // end isEmpty

template<class ItemType>
bool LinkedBag<ItemType>::isFull() const
{
	return false;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCapacity() const
{
	return getCurrentSize();
}  // end isEmpty


template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (headPtr is null if chain is empty) 
    if (head_ptr == nullptr)
		head_ptr = new Node<ItemType>(newEntry);
	else
		head_ptr = new Node<ItemType>(newEntry, head_ptr);
	++itemCount;
	return true;
}  // end add

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
	Node<ItemType>* to_delete;
	
	if (head_ptr == nullptr) return false;

	if (head_ptr->getItem() == anEntry)
	{
		to_delete = head_ptr;
		head_ptr = head_ptr->getNext();
		delete to_delete;
		--itemCount;
		return true;
	}

	Node<ItemType>* curr = head_ptr;
	while (curr != nullptr && curr->getNext() != nullptr)
	{
		if (curr->getNext()->getItem() == anEntry)
		{
			to_delete = curr->getNext();
			curr->setNext(to_delete->getNext());
			delete to_delete;
			--itemCount;
			return true;
		}
		curr = curr->getNext();
	}
	return false;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
   Node<ItemType>* nodeToDeletePtr = head_ptr;
   while (head_ptr != nullptr)
   {
      head_ptr = head_ptr->getNext();
      
      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      
      nodeToDeletePtr = head_ptr;
   }  // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr
   
	itemCount = 0;
}  // end clear


template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
   int counter = 0;
   Node<ItemType>* curPtr = head_ptr;
   while ((curPtr != nullptr) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      } // end if
      
      counter++;
      curPtr = curPtr->getNext();
   } // end while
   
	return frequency;
}  // end getFrequencyOf

// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = head_ptr;
   
   while (!found && (curPtr != nullptr))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while
   
   return curPtr;
} // end getPointerTo


template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
	vector<ItemType> stuff;
	
	Node<ItemType>* curr = head_ptr;
	while (curr != nullptr)	
	{
		stuff.push_back(curr->getItem());
		curr = curr->getNext();
	}
	return stuff;
}  // end isEmpty
