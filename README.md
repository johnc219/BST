A templated binary search tree data structure header file.
API:
BST()
~BST()
void insert_val(T val)
void insert_val(std::vector<T> val_vector)
void insert_val(std::list<T> val_list)
bool delete_val(T val)
T get_max()
T get_min()
T get_successor()
std::vector<T> get_vector()
std::list<T> get_list()
bool exists(T val)
int get_length()
void print_tree()

