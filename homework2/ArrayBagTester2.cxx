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
		
		int tamales = 0;
		for (int i = 0; i < aBag.getCapacity(); ++i)
		{
			aBag.add("tamale");
			++tamales;
		}
			
		if (aBag.getCurrentSize() != aBag.getCapacity())
			cout << "Bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Bag after adding has right size; that is good" << endl;
		
		// try adding to a 'full' ArrayBag to trigger resizing
		aBag.add("tamale");	++tamales;
		
		// check if we can count up how often an item appears in the ArrayBag
		if (aBag.getFrequencyOf("tamale") != tamales)
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
			
		
		aBag.add("apple");
		aBag.add("banana");
		aBag.add("cherries");
		// test toArray on the Bag
		vector<string> contents = aBag.toVector();
		cout << "Here is a vector of the contents of a bag with 3 items" << endl;
		for (int i = 0; i < aBag.getCurrentSize(); ++i)
			cout << contents[i] << " ";
		cout << endl;

		// test copy constructor on the bag
		cout << "Testing the copy constructor by making another bag with 3 items" << endl;
		ArrayBag<string> fruitBag = aBag;
		
		cout << "Adding an item to the copied bag" << endl;
		fruitBag.add("durian");
		
		cout << "Here is a vector of the contents of the copied bag with 4 items" << endl;
		vector<string> otherContents = fruitBag.toVector();
		for (int i = 0; i < fruitBag.getCurrentSize(); ++i)
			cout << otherContents[i] << " ";
		cout << endl;
			
		ArrayBag<string> newBag;
		newBag = aBag;
		otherContents = newBag.toVector();
		for (int i = 0; i < newBag.getCurrentSize(); ++i)
			cout << otherContents[i] << " ";
		cout << endl;
		
		/*
		//Exam additions
		ArrayBag<string> colorBag;
		colorBag.add("yellow"); colorBag.add("green"); colorBag.add("purple"); colorBag.add("blue"); 
		
		ArrayBag<string> superBag[2][4];
		vector<string> fruitVector = fruitBag.toVector();
		vector<string> colorVector = colorBag.toVector();
		for(int i = 0; i < 4; i++)
		{
			superBag[0][i] = fruitVector[i];
			//superBag[1][i] = colorVector[i];
		}
		* */
	}

