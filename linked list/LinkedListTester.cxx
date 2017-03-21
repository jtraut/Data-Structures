//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 11-2.

#include <iostream>
#include <string>
#include "LinkedBag.h"

using namespace std;



int main()
{
	LinkedBag<string> papasBag;
	papasBag.add("Pippin");
	
	vector<string> papasVector;
	papasVector = papasBag.toVector();
	cout << "Bag contents are" << endl;
	for (unsigned int q = 0; q < papasVector.size(); ++q)
		cout << papasVector[q] << endl;
	cout << endl;	
	papasBag.add("Frodo");
	papasVector = papasBag.toVector();
	cout << "Bag contents are" << endl;
	for (unsigned int q = 0; q < papasVector.size(); ++q)
		cout << papasVector[q] << endl;
	cout << endl;
	papasBag.add("Gollum");	
	papasVector = papasBag.toVector();
	cout << "Bag contents are" << endl;
	for (unsigned int q = 0; q < papasVector.size(); ++q)
		cout << papasVector[q] << endl;
	cout << endl;
	
	papasBag.remove("Pippin");
	papasVector = papasBag.toVector();
	cout << "Bag contents are" << endl;
	for (unsigned int q = 0; q < papasVector.size(); ++q)
		cout << papasVector[q] << endl;
	cout << endl;
	
}  // end main

