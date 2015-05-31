/************************************************  Preprocessing  ************************************************/

#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <list>
#include <string>

/************************************************  Used Data Structures  ************************************************/

// node data structure to hold important fields
template<typename T>
struct node{
	T value;
	node<T> *parent;
	node<T> *left;
	node<T> *right;
};

// data structure to hold important info about the results of searching for a a value in a tree
template<typename T>
struct search_result{
	bool found;
	char direction;
	node<T> *result_node;
};

/************************************************  API  ************************************************/

// Templated BST header file
// Allows for inserting, deleting, and searching in Theta(log(h)) where h is the height of the tree
// Allows finding the max, min, and successor in Theta(log(h))
// Allows for sorting a vector or list in Theta(nlog(h)) where n is the number of nodes in the tree
template<class T> 
class BST{

	public:

		/**
		 *	Constructor to initialize member variables
		 */
		BST();

		/**
		 *	Constructor with the option to add a name
		 *	@param name what the BST will be named
		 */
		BST(std::string name);

		/**
		 *	Destructor that recursively deletes any dynamically allocated memory
		 */
		~BST();
		
		/**
		 *	Insert a value into the binary search tree object
		 *	@param val the value to be inserted
		 */
		void insert_val(T val);
		
		/**
		 *	Insert all the elements in a vector into the BST object
		 *	@param val_vector the vector of values to be inserted
		 */ 
		void insert_val(std::vector<T> val_vector);
		
		/**
		 *	Insert all the elements in a list into the BST object
		 *	@param val_list the list of values to be inserted
		 */
		void insert_val(std::list<T> val_list);
		
		/**
		 *	Delete a value from the BST if it exists
		 *	@param val the value to be deleted from the BST
		 *	@return returns true if the value was deleted, returns false if not
		 */
		bool delete_val(T val);
		
		/**
		 *	Get the maximum value in the BST
		 *	@return returns the max value. If the BST is empty, it returns zero
		 */
		T get_max();
		
		/**
		 *	Get the minimum value in the BST
		 *	@return returns the min value. If the BST is empty, it retursn zero
		 */
		T get_min();
		
		/**
		 *	Get the smallest element that follows after the input value
		 *	@param val the input value
		 *	@return returns the next element. If the argument does not have a successor or the BST is empty, zero is returned
		 */
		T get_successor(T val);

		/**
		 *	Get a sorted vector representation of the BST
		 *	@return returns the sorted vector
		 */
		std::vector<T> get_vector();
		
		/**
		 *	Get a sorted list representation of the BST
		 *	@return retursn the sorted list
		 */
		std::list<T> get_list();
		
		/**
		 *	Check if a value is in the BST
		 *	@param val the value that is being checked
		 *	@return returns true if val is in the BST, false otehrwise
		 */
		bool exists(T val);
		
		/**
		 *	Returns the number of nodes in the BST
		 *	@return returns the length member variable
		 */
		int get_length();
		
		/**
		 *	Prints the contents of the BST in nondecreasing sorted order
		 */
		void print_tree();

		/**
		 * Get the root value
		 * @returns the value in the root node
		 */
		T get_root();

	private:

		/**
		 *	Recursively search for the node that contains the maximum value in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return the node pointer that points to the node with the maximum value
		 */
		node<T> *search_max(node<T> *location);

		/**
		 *	Recusively search for the node that contains the minimum value in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return the node pointer that points to the node with the minimum value
		 */
		node<T> *search_min(node<T> *location);
		
		/**
		 *	Recursively search for a node that contains the desired value
		 *	@param val the value that is being searched for in the BST
		 *	@param location the node pointer to begin the search from
		 *	@return returns a search_result data structure that contains details about the search result
		 */
		search_result<T> search_val(T val, node<T> *location); 

		/**
		 *	Search for the successor of a desired node
		 *	@param location the pointer to the node whose successor is desired
		 *	@return return the pointer node to the successor node. If the desired node has no successor, NULL is returned
		 */
		node<T> *search_successor(node<T> *location);

		/**
		 *	Traverse the BST. 2 modes:
		 *	@param location the pointer to the node that is being traversed
		 *	@param function the mode
		 *		function == 0 -> traverse in order, print each node value
		 *		function == 1 -> traverse in post order, recursively deleting each node
		 */
		void order(node<T> *location, int function);

		/**
		 *	Delete a specified node
		 *	@param location the pointer to the node to be deleted
		 */
		void delete_node(node<T> *location);

		/**
		 *	Fill a vector with the contents of the BST by reference by traversing the BST in order. The vector is sorted.
		 *	@param location the pointer to the node whose value will be pushed into the vector
		 */
		void fill_vector(std::vector<T>& val_vector, node<T> *location);

		/**
		 *	Fill a list with the contents of the BST by reference by traversing the BST in order. The list is sorted.
		 *	@param location the pointer to the node whose value will be pushed into the list
		 */
		void fill_list(std::list<T>& val_list, node<T> *location);
		
		// Pointer to the node that is the root of the BST
		node<T> *root;

		// The number of nodes in the BST
		int length;

		std::string name;
};

/************************************************  Implementation  ************************************************/

// Constructor
template<class T>
BST<T>::BST(){
	root = NULL;
	length = 0;
	name = "untitled BST";
}

// Constructor with name
template<class T>
BST<T>::BST(std::string name){
	root = NULL;
	length = 0;
	this->name = name;
}

// Destructor
template<class T>
BST<T>::~BST(){
	std::cout << std::endl << "Deleting BST <" << name << ">" << std::endl;
	if (length > 0)
		order(root, 1);
}

// insert a value
template<class T>
void BST<T>::insert_val(T val){
	search_result<T> result = search_val(val, root);
	if (result.found == true){
		node<T> *ptr = new node<T>;
		ptr->value = val;
		ptr->parent = result.result_node; 
		ptr->left = (result.result_node)->left;
		ptr->right = NULL;
		(result.result_node)->left = ptr;
		std::cout << "inserted a copy of " << val << std::endl;
	}
	else{
		if (result.direction == 'R'){
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = result.result_node;
			ptr->left = NULL;
			ptr->right = NULL;
			(result.result_node)->right = ptr;
			std::cout << "inserted a new node to the right of " << ptr->parent->value << " with value " << val << std::endl;
		}
		else if (result.direction == 'L'){
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = result.result_node;
			ptr->left = NULL;
			ptr->right = NULL;
			(result.result_node)->left = ptr;
			std::cout << "inserted a new node to the left of " << ptr->parent->value << " with value " << val << std::endl;
		}
		else if (result.direction == 'E'){
			std::cout << "Error" << std::endl;
			length--;
		}
		else{
			node<T> *ptr = new node<T>;
			ptr->value = val;
			ptr->parent = NULL;
			ptr->left = NULL;
			ptr->right = NULL;
			root = ptr;
			std::cout << "empty BST, inserting " << val << std::endl;
		}
	}
	length++;
}

// insert a vector
template<class T>
void BST<T>::insert_val(std::vector<T> val_vector){
	for (typename std::vector<T>::iterator it = val_vector.begin(); it != val_vector.end(); it++){
		insert_val(*it);
	}
}

// insert a list
template<class T>
void BST<T>::insert_val(std::list<T> val_list){
	for (typename std::list<T>::iterator it = val_list.begin(); it != val_list.end(); it++){
		insert_val(*it);
	}
}

// delete a value
template<class T>
bool BST<T>::delete_val(T val){
	search_result<T> result = search_val(val, root);
	node<T> *location = result.result_node;
	if (result.found){
		delete_node(location);
		return true;
	}
	else{
		std::cout << val << " not found in tree, nothing deleted" << std::endl; 
		return false;
	}
}

// delete a node
template<class T>
void BST<T>::delete_node(node<T> *location){
	if (location->left == NULL && location->right == NULL){
		std::cout << "deleting " << location->value << std::endl;
		if (location->parent != NULL){
			if (location->parent->left == location){
				location->parent->left = NULL;
			}
			else if (location->parent->right == location){
				location->parent->right = NULL;
			}
		}
		delete location;
		length--;
		return;
	}
	// one child on left
	else if (location->left != NULL && location->right == NULL){
		node<T> *left = location->left;
		left->parent = location->parent;
		// is root
		if (location->parent == NULL){
			std::cout << "deleting root " << location->value << "\tnew root: " << left->value << std::endl; 
			root = left;
		}
		else if (location->parent->left == location){
			std::cout << "deleting " << location->value << std::endl;
			location->parent->left = left;
		}
		else if (location->parent->right == location){
			std::cout << "deleting " << location->value << std::endl;
			location->parent->right = left;
		}
		delete location;
		length--;
		return;
	}
	// one child on right
	else if (location->left == NULL && location->right != NULL){
		node<T> *right = location->right;
		right->parent = location->parent;
		// is root
		if (location->parent == NULL){
			std::cout << "deleting root " << location->value << "\tnew root: " << right->value << std::endl;
			root = right;
		}
		else if (location->parent->left == location){
			std::cout << "deleting " << location->value << std::endl;
			location->parent->left = right;
		}
		else if (location->parent->right == location){
			std::cout << "deleting " << location->value << std::endl;
			location->parent->right = right;
		}
		delete location;
		length--;
		return;
	}
	// two children
	else{
		node<T> *successor_node = search_successor(location);
		T temp_val = location->value;
		location->value = successor_node->value;
		successor_node->value = temp_val;
		delete_node(successor_node);
		return;
	}
}

// get the max value
template<class T>
T BST<T>::get_max(){
	node<T> *max_node = search_max(root);
	if (max_node != NULL){
		std::cout << "max: " << max_node->value << std::endl;
		return max_node->value;
	}
	else{
		std::cout << "Warning: empty BST" << std::endl;
		return 0;
	}
}

// get the min value
template<class T>
T BST<T>::get_min(){
	node<T> *min_node = search_min(root);
	if (min_node != NULL){
		std::cout << "min: " << min_node->value << std::endl;
		return min_node->value;
	}
	else{
		std::cout << "Warning: empty BST" << std::endl;
		return 0;
	}
}

// get the max node
template<class T>
node<T>* BST<T>::search_max(node<T> *location){
	if (location->right == NULL){
		if (length == 0){
			return NULL;
		}
		return location;
	}
	else{
		return search_max(location->right);
	}
}

// get the min node
template<class T>
node<T>* BST<T>::search_min(node<T> *location){
	if (location->left == NULL){
		if (length == 0){
			return NULL;
		}
		return location;
	}
	else{
		return search_min(location->left);
	}
}

// get the successor value
template<class T>
T BST<T>::get_successor(T val){
	search_result<T> location = search_val(val, root);
	if (location.found){
		node<T> *successor_node = search_successor(location.result_node);
		if (successor_node != NULL){
			std::cout << "successor of " << val << ": " << successor_node->value << std::endl;
			return successor_node->value;
		}
		else{
			std::cout << "No successor. Default value zero" << std::endl;
			return 0;
		}
	}
	else{
		std::cout << "Value not in tree. Default value zero" << std::endl;
		return 0;
	}
}	

// get the successor node
template<class T>
node<T> *BST<T>::search_successor(node<T> * location){
	if (location->right != NULL){
		return search_min(location->right);
	}
	else{
		node<T> *parent = location->parent;
		node<T> *child = location;
		while (parent != NULL && parent->left != child){
			child = parent;
			parent = parent->parent;
		}
		return parent;
	}
}

// get a list
template<class T>
std::list<T> BST<T>::get_list(){
	std::list<T> l;
	fill_list(l, root);
	return l;
}

// fill the list
template<class T>
void BST<T>::fill_list(std::list<T>& val_list, node<T> *location){
	if (length > 0){
		if (location->left != NULL){
			fill_list(val_list, location->left);
		}
		val_list.push_back(location->value);
		if (location->right != NULL){
			fill_list(val_list, location->right);
		}
	}
}

// get a vector 
template<class T>
std::vector<T> BST<T>::get_vector(){
	std::vector<T> v;
	fill_vector(v, root);
	return v;
}

// fill the vector
template<class T>
void BST<T>::fill_vector(std::vector<T>& val_vector, node<T> *location){
	if (length > 0){
		if (location->left != NULL){
			fill_vector(val_vector, location->left);
		}
		val_vector.push_back(location->value);
		if (location->right != NULL){
			fill_vector(val_vector, location->right);
		}
	}
}

// check if val exists
template<class T>
bool BST<T>::exists(T val){
	search_result<T> result = search_val(val, root);
	if (result.found){
		std::cout << val << " exists in the tree" << std::endl;
		return true;
	}
	else{
		std::cout << val << " doesn't exist in the tree" << std::endl;
		return false;
	}
}

// traverse bst
template<class T>
void BST<T>::order(node<T> *location, int function){
	// traverse in order to get the sorted tree
	// left, root, right
	if (function == 0){
		if (location->left != NULL){
			order(location->left, function);
		}
		std::cout << location->value << std::endl;
		if (location->right != NULL){
			order(location->right, function);
		}

	}
	// traverse post order to recursively delete items
	// left, right, root
	else if (function == 1){
		if (location->left != NULL){
			order(location->left, function);
		}
		if (location->right != NULL){
			order(location->right, function);
		}
		length--;
		std::cout << "deleting " << location->value << "\t" << length << " items remaining" << std::endl;
		delete location;
	}
	else{
		std::cout << "no action" << std::endl;
	}
}

// search for a node
template<class T>
search_result<T> BST<T>::search_val(T val, node<T> *location){
	if (location == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'N';
		result.result_node = NULL;
		return result;
	}
	else if (location->value == val){
		search_result<T> result;
		result.found = true;
		result.direction = 'N';
		result.result_node = location;
		return result;
	}
	else if (val > location->value && location->right == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'R';
		result.result_node = location;
		return result;
	}
	else if (val > location->value && location->right != NULL){
		return search_val(val, location->right);
	}
	else if (val < location->value && location->left == NULL){
		search_result<T> result;
		result.found = false;
		result.direction = 'L';
		result.result_node = location;
		return result;
	}
	else if (val < location->value && location->left != NULL){
		return search_val(val, location->left);
	}
	else{
		search_result<T> result;
		result.found = false;
		result.direction = 'E';
		result.result_node = NULL;
		return result;
	}
}

// get the number of nodes
template<class T>
int BST<T>::get_length(){
	return length;
}

// print contents in order
template<class T>
void BST<T>::print_tree(){
	std::cout << std::endl << "BST <" << name << "> contents: " << std::endl;
	if (length > 0)
		order(root, 0);
	else{
		std::cout << std::endl << "BST <" << name << "> is empty" << std::endl;
	}
}

template<class T>
T BST<T>::get_root(){
	if (length > 0){
		std::cout << "BST <" << name << "> root: " << root->value << std::endl;
		return root->value;
	} else{
		std::cout << "BST <" << name << "> is empty" << std::endl;
		return 0;
	}
}

#endif