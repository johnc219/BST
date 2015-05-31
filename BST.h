#ifndef BST_H
#define BST_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <list>

template<typename T>
struct node{
	T value;
	node<T> *parent;
	node<T> *left;
	node<T> *right;
};

template<typename T>
struct search_result{
	bool found;
	char direction;
	node<T> *result_node;
};

template<class T> 
class BST{

	public:
		BST();
		~BST();
		
		void insert_val(T val);
		void insert_val(std::vector<T> val_vector);
		void insert_val(std::list<T> val_list);
		bool delete_val(T val);
		
		T get_max();
		T get_min();
		T get_successor(T val);
		std::vector<T> get_vector();
		std::list<T> get_list();
		bool exists(T val);
		int get_length();
		void print_tree();

	private:
		node<T> *search_max(node<T> *location);
		node<T> *search_min(node<T> *location);
		search_result<T> search_val(T val, node<T> *location); 
		node<T> *search_successor(node<T> *location);
		void order(node<T> *location, int function);
		void delete_node(node<T> *location);
		void fill_vector(std::vector<T>& val_vector, node<T> *location);
		void fill_list(std::list<T>& val_list, node<T> *location);
		
		node<T> *root;
		int length;
};

template<class T>
std::list<T> BST<T>::get_list(){
	std::list<T> l;
	fill_list(l, root);
	return l;
}

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

template<class T>
std::vector<T> BST<T>::get_vector(){
	std::vector<T> v;
	fill_vector(v, root);
	return v;
}

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

template<class T>
void BST<T>::insert_val(std::vector<T> val_vector){
	for (typename std::vector<T>::iterator it = val_vector.begin(); it != val_vector.end(); it++){
		insert_val(*it);
	}
}

template<class T>
void BST<T>::insert_val(std::list<T> val_list){
	for (typename std::list<T>::iterator it = val_list.begin(); it != val_list.end(); it++){
		insert_val(*it);
	}
}

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

template<class T>
BST<T>::BST(){
	root = NULL;
	length = 0;
}

template<class T>
BST<T>::~BST(){
	if (length > 0)
		order(root, 1);
}

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

template<class T>
int BST<T>::get_length(){
	return length;
}

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

template<class T>
void BST<T>::print_tree(){
	std::cout << "BST contents: " << std::endl;
	order(root, 0);
}

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

#endif