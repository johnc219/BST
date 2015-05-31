#include "BST.h"

#include <iostream>
#include <cstdlib>

int main(){

	srand(time(NULL));
	
	std::vector<int> rand_v;
	std::list<int> rand_l;
	
	BST<int> manualBST("BST from one by one values");
	BST<int> vectorBST("BST from vector");
	BST<int> listBST("BST from list");

	for (int i = 0; i < 15; i++){
		int num = rand() % 500;
		manualBST.insert_val(num);
		rand_v.push_back(num);
		rand_l.push_back(num);
	}


	vectorBST.insert_val(rand_v);
	listBST.insert_val(rand_l);

	int error_count = 0;
	for (int i = 0; i < vectorBST.get_length(); i++){
		if (!(vectorBST.exists(rand_v[i]) && listBST.exists(rand_v[i]) && manualBST.exists(rand_v[i]))){
			error_count++;
		} 
	}
	std::cout << "error_count: " << error_count << std::endl;

	vectorBST.print_tree();
	listBST.get_root();

	return 0;
}