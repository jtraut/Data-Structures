// FILE: BSTreeBag.cxx
// TEMPLATE CLASS IMPLEMENTED: BSTreeBag<ItemType> (see BSTreeBag.h for documentation)
// INVARIANT of the ADT:
//   root_ptr is the root pointer of a binary search tree that contains the
//   BSTreeBag's items.

#include <cassert>
#include <cstdlib>

namespace bst2270
{
    template <class ItemType>
	void bst_remove_max(binary_tree_node<ItemType>*& root_ptr, ItemType& removed)
	// Precondition: root_ptr is a root pointer of a non-empty binary 
	// search tree.
	// Postcondition: The largest item in the binary search tree has been
	// removed, and root_ptr now points to the root of the new (smaller) 
	// binary search tree. The reference parameter, removed, has been set 
	// to a copy of the removed item.
	{
		if (root_ptr->right()){
			bst_remove_max(root_ptr->right(), removed);
		}
		else{
			removed = root_ptr->data();
			binary_tree_node<ItemType>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->left();
			delete old_root_ptr;
			old_root_ptr = NULL;
		}
	}

    template <class ItemType>
	bool bst_remove(binary_tree_node<ItemType>*& root_ptr, const ItemType& target)
	// Precondition: root_ptr is a root pointer of a binary search tree 
	// or may be nullptr for an empty tree).
	// Postcondition: If target was in the tree, then one copy of target
	// has been removed, and root_ptr now points to the root of the new 
	// (smaller) binary search tree. In this case the function returns true.
	// If target was not in the tree, then the tree is unchanged (and the
	// function returns false).
	{ 
		if(root_ptr == nullptr)
			return 0;
		if(target < root_ptr->data()){
			return bst_remove(root_ptr->left(), target);
		}
		if(target > root_ptr->data()){
			return bst_remove(root_ptr->right(), target);
		}
		
		//Found target
		if(root_ptr->left() == nullptr){
			binary_tree_node<ItemType>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->right();
			delete old_root_ptr;
			return 1;
		}
		bst_remove_max(root_ptr->left(), root_ptr->data());
		return true;
	}

    template <class ItemType>
	unsigned int bst_remove_all
	(binary_tree_node<ItemType>*& root_ptr, const ItemType& target)
	// Precondition: root_ptr is a root pointer of a binary search tree 
	// or may be nullptr for an empty tree).
	// Postcondition: All copies of target have been removed from the tree
	// has been removed, and root_ptr now points to the root of the new 
	// (smaller) binary search tree. The return value tells how many copies
	// of the target were removed.
	{
		if(root_ptr == nullptr)
			return 0;
		if(target < root_ptr->data()){
			return bst_remove_all(root_ptr->left(), target);
		}
		if(target > root_ptr->data()){
			return bst_remove_all(root_ptr->right(), target);
		}
		
		//Found target
		if(root_ptr->left() == nullptr){
			binary_tree_node<ItemType>* old_root_ptr = root_ptr;
			root_ptr = root_ptr->right();
			delete old_root_ptr;
			return 1;
		}
		bst_remove_max(root_ptr->left(), root_ptr->data());
		return 1 + bst_remove_all(root_ptr, target);
		return true;
	}

    template <class ItemType>
	BSTreeBag<ItemType>::BSTreeBag()
	{
		root_ptr = nullptr;
	}
	
    template <class ItemType>
	BSTreeBag<ItemType>::BSTreeBag(const BSTreeBag<ItemType>& source)
	// Library facilities used: bintree.h
	{
		root_ptr = tree_copy(source.root_ptr);
	}

    template <class ItemType>
	BSTreeBag<ItemType>::~BSTreeBag( )
	// Header file used: bintree.h
	{
		tree_clear(root_ptr);
	}

    template <class ItemType>
	unsigned int BSTreeBag<ItemType>::size( ) const
	// Header file used: bintree.h
	{
		return tree_size(root_ptr);
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::insert(const ItemType& entry)
	// Header file used: bintree.h
	{
		if(root_ptr == nullptr){
			root_ptr = new binary_tree_node<ItemType>(entry);
			return;
		}
		
		binary_tree_node<ItemType>* cursor = root_ptr;
		
		while(true){
			if(entry <= cursor->data() && cursor->left() != nullptr){
				cursor = cursor->left();
			}
			else if(entry > cursor->data() && cursor->right() != nullptr){
				cursor = cursor->right();
			}
			else{
				if(entry <= cursor->data()){
					cursor->left() = new binary_tree_node<ItemType>(entry);
					return;
				}	
				else{
					cursor->right() = new binary_tree_node<ItemType>(entry);
					return;
				}
			}
		}
	}

    template <class ItemType>
	unsigned int BSTreeBag<ItemType>::count(const ItemType& target) const
	{
		unsigned int answer = 0;
		
		if(root_ptr == nullptr)
			return 0;
		
		binary_tree_node<ItemType>* cursor = root_ptr;
		
		while(true){
			if(cursor->data() == target)
				answer++;
			if(target <= cursor->data() && cursor->left() != nullptr)
				cursor = cursor->left();
			else if(target > cursor->data() && cursor->right() != nullptr)
				cursor = cursor->right();
			else
				return answer;
		}
	}

    template <class ItemType>
	unsigned int BSTreeBag<ItemType>::erase(const ItemType& target)
	{
		return bst_remove_all(root_ptr, target);
	}

    template <class ItemType>
	bool BSTreeBag<ItemType>::erase_one(const ItemType& target)
	{
		return bst_remove(root_ptr, target);
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::operator =(const BSTreeBag<ItemType>& source)
    {
		if (this == &source)
		    return;
		tree_clear(root_ptr);
		root_ptr = tree_copy(source.root_ptr);
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::operator +=(const BSTreeBag<ItemType>& addend)
	{
		if (root_ptr == addend.root_ptr)
		{
			BSTreeBag<ItemType> copy = addend;
			insert_all(copy.root_ptr);
		}
		else
			insert_all(addend.root_ptr);
	}

	template <class ItemType>
	BSTreeBag<ItemType> operator +(const BSTreeBag<ItemType>& b1, const BSTreeBag<ItemType>& b2)
	{
		BSTreeBag<ItemType> answer = b1;
		answer += b2;
		return answer;
	}

    template <class ItemType>
	void BSTreeBag<ItemType>::insert_all(binary_tree_node<ItemType>* addroot_ptr)
        // Precondition: addroot_ptr is the root pointer of a binary search tree that
        // is separate for the binary search tree of the BSTreeBag that activated this
        // method.
        // Postcondition: All the items from the addroot_ptr's binary search tree
        // have been added to the binary search tree of the BSTreeBag that activated this
        // method.
	{
		if (addroot_ptr != nullptr)
		{
			insert(addroot_ptr->data( ));
			insert_all(addroot_ptr->left( ));
			insert_all(addroot_ptr->right( ));
		}
	}
	
}
