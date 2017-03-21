#include <iostream>
#include <string>
#include "ArrayBag.h"

using namespace std;

int main()
	{
		// here we call the ArrayBag constructor; this particular bag stores strings 
		ArrayBag<string> aBag;
		
		// here we call the isEmpty function on a new ArrayBag 
		if (aBag.isEmpty())
			cout << "New bag is created empty; that is good" << endl;
		else
			cout << "New bag is created with stuff; not so good" << endl;
			
		// here we call the getCapacity function on a new ArrayBag 
		if (aBag.getCapacity() > 0)
			cout << "New bag is created with non-zero capacity; that is good" << endl;
		else
			cout << "New bag is created with zero capacity; not so good" << endl;

		// here we add a couple of things 
		aBag.add("tostada");
		aBag.add("tamale");
		aBag.add("taco");

		// here we check if the ArrayBag is empty
		if (aBag.isEmpty())
			cout << "Bag after adding thinks it is empty; that is not so good" << endl;
		else
			cout << "Bag after adding thinks it is not empty; that is good" << endl;
			
		// here we check if it knows its own size
		if (aBag.getCurrentSize() != 3)
			cout << "Bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Bag after adding has right size; that is good" << endl;
		
		if (aBag.contains("tamale") == false)
			cout << "Bag can't find added items; that is not so good" << endl;
		else
			cout << "Bag can find added items; that is good" << endl;
		
		if (aBag.contains("torta") == true)
			cout << "Bag can find items we never added; that is not so good" << endl;
		else
			cout << "Bag doesn't find items we never added; that is good" << endl;
			
		// here we check what happens if we ask to remove something not in the ArrayBag
		aBag.remove("torta");
		
		// here we check if the ArrayBag knows its own size after a non-event removal
		if (aBag.getCurrentSize() != 3)
			cout << "Bag should be the same size as before but isn't; that is not so good" << endl;
		else
			cout << "Bag is the same size as before; that is good" << endl;
		
		// here we remove something in the ArrayBag
		aBag.remove("tamale");
		
		// here we check if the size has changed
		if (aBag.getCurrentSize() != 2)
			cout << "Bag should be smaller than before but isn't; that is not so good" << endl;
		else
			cout << "Bag is the right size after removing one item; that is good" << endl;
		
		// empty the bag
		aBag.clear();
		
		// check the size of the empty bag
		if (aBag.getCurrentSize() != 0)
			cout << "Bag after clearing has wrong size; that is not so good" << endl;
		else
			cout << "Bag after clearing has right size; that is good" << endl;
		
		for (int i = 0; i < aBag.getCapacity(); ++i)
			aBag.add("tamale");
			
		if (aBag.getCurrentSize() != aBag.getCapacity())
			cout << "Bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Bag after adding has right size; that is good" << endl;
		
		// try adding to a full ArrayBag
		aBag.add("tamale");
		
		// check that this has not changed the size
		if (aBag.getCurrentSize() != aBag.getCapacity())
			cout << "Full bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Full bag after adding has right size; that is good" << endl;
			
		// check if the ArrayBag is now full
		if (aBag.isFull() == false)
			cout << "Full bag doesn't know it's full; that is not so good" << endl;
		else
			cout << "Full bag knows it's full; that is good" << endl;
		
		// check if we can count up how often an item appears in the ArrayBag
		if (aBag.getFrequencyOf("tamale") != aBag.getCapacity())
			cout << "Bag can't count items correctly when they are present; that is not so good" << endl;
		else
			cout << "Bag can count items correctly when they are present; that is good" << endl;
		
		// check if we get the right answer for an item that isn't in the ArrayBag
		if (aBag.getFrequencyOf("torta") != 0)
			cout << "Bag can't count items correctly when they are absent; that is not so good" << endl;
		else
			cout << "Bag can count items correctly when they are absent; that is good" << endl;
				
		// use remove to empty the Bag
		for (int i = 0; i < aBag.getCapacity(); ++i)
			aBag.remove("tamale");
			
		// check that remove has left the size correct
		if (aBag.getCurrentSize() != 0)
			cout << "Size of bag is incorrect after removing all the items; that is not so good" << endl;
		else
			cout << "Size of bag after removing all the items is correct; that is good" << endl;
			
		// check if items are removed and replaced correctly 
		ArrayBag<int> dBag;		
		for (int i = 1; i < 11; i++)
		{
			dBag.add(i);
		}
		cout << "" << endl;
		cout << "New bag contents: ";
	
		vector<int> bagItems1 = dBag.toVector();
		for (int i = 0; i < (int)bagItems1.size(); i++)
		{
			cout << bagItems1[i] << " "; 
		}
		cout << endl << endl; 
		
		cout << "Removing number 5" << endl;
		dBag.remove(5);
		cout << "Checking bag items" << endl << endl;

		
		for (int i = 0; i <= dBag.getCurrentSize(); i++)
		{
			bool hasNum = dBag.contains(i+1);
			if (hasNum)
			{
				cout << "Bag contains: " << (i+1) << endl;
			}
			else 
			{
				cout << "Bag does not contain: " << i+1 << endl;
			}
		}
		cout << endl;
		cout << "The resulting bag: "; 
		vector<int> bagItems2 = dBag.toVector();
		for (int i = 0; i < (int)bagItems2.size(); i++)
		{
			cout << bagItems2[i] << " "; 
		}
	}
	
	

