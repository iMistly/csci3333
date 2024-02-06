// *****************************************************************
// Class:			CSCI3333, Supplemental Lab Exercises
// Lab 1:			Binary search tree
// Comment:			The code here is meant to be revised.
//-----------------------------------------------------------------
// Description: This program is to implement the binary search tree 
// class template
// *****************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>

#include "lab3333_1_head.h"	


using namespace std; 

int main()
{
	/**********************************************************
	 Part A: Some practice
	 **********************************************************/
	//var decarations
	unsigned int seed;					//a random seed
	int num;							//to hold an int value
	binarySearchTree<int> tree;			//create a list of int type
	char tag; 
	
	cout<<"loading the list with random numbers between 0 and 666 ... "<<endl; 

	cout<<"Enter a random seed => ";	//get the random seed
	cin >> seed; 
	srand(seed);						//set the randon seed

	for (int i=0; i <10 ; i++)			//insert 50 random numbers into the list
	{
		num = rand()%31; 
		cout<<num<<"  ";
		tree.insert(num);
	}
	cout<<endl; 

	cout<<"inorder traversal ..... "<<endl; 
	tree.inOrderTraversal(); 
	cout<<"preorder traversal ..... "<<endl; 
	tree.preOrderTraversal(); 
	cout<<"postorder traversal ..... "<<endl; 
	tree.postOrderTraversal(); 
	cout<<"tree height is "<< tree.treeHeight()<<endl; 
	cout<<"tree node count is "<< tree.treeNodeCount()<<endl; 
	cout<<"tree leave count is "<< tree.treeLeaveCount()<<endl; 

	cout<<endl; 
	
	//test delete and search
	while (true)
	{
		cout<<"Want to play with searching or deletion(s/d)? "<<endl; 
		cout<<"Enter q to stop "; 
		cin>>tag; 
		switch (tag)
		{
		case 'd':
		case 'D':
				cout<<"What to be deleted? "; 
				cin>> num; 
				tree.remove(num); 
				tree.inOrderTraversal(); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>num; 
				if(tree.find(num))
					cout<<"found "<< num <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<num<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag == 'q' || tag == 'Q')
			break; 
	}

	/**********************************************************************
	 Part B: Try to create a binary search tree of strings and practice 
	 basic tree operations such as insertion, deletion, search, etc.
	 **********************************************************************/
	
	//Write your code here

	/**********************************************************************
	 Part C: First define a personType class with three data members 
	 (string name, int ID, and double grade). Second, create binary search
	 tree of personType. Third, practice basic tree operations such as 
	 insertion, deletion, search, etc.
	 ***********************************************************************/
	
	//Write your code here
	
	/******************************************************************************************
	 Part D: Use binary search tree to sort a list of 1,000,000 random integers.
	 (1) Use a random number generator to generate a list of 1,000,000 random integers 
		 and save them into a file "data.txt"
	 (2) Create a binary search tree of int type 
		 and use this tree to sort those integers in "data.txt". Record the time of the sorting. 
	 (3) Use insertionSort, selectionSort, bubbleSort, megerSort, and quickSort to sort
		 the same list of the integers, and record the times of those sorting algorithms
	 (4) Prepare a table to report the time performance of the sorting algorithms. 
	 *******************************************************************************************/
	//Write your code here


	//complete the program
	return 0; 
}