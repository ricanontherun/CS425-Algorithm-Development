#include <iostream>

template <typename T>
class BinarySearchTree
{
	public:
		BinarySearchTree()
			: root(nullptr)
		{};

		bool insert(T object) {
			if ( this->root == nullptr ) {
				std::cout << "Setting new root\n";
				this->root = new Node(object);
			} else {
				return this->insert(object, this->root);
			}

			return true;
		}

	private:
		struct Node
		{
			T data;
			Node * left; // Less than
			Node * right; // greater than.

			Node(T data, Node * left = nullptr, Node * right = nullptr)
				: data(data),
					left(left),
					right(right)
			{}
		};

		bool insert(T object, Node * root) {
			bool ret = true;

			if ( root == nullptr ) {
				std::cout << "Setting new root\n";
				root = new Node(object);
			} else if ( object < root->data ) {
				std::cout << "Going left\n";
				this->insert(object, root->left);
			} else if ( object > root->data ) {
				std::cout << "Going right\n";
				this->insert(object, root->right);
			} else {
				std::cout << "Found a duplicate\n";
				ret = false;
			}

			return ret;
		}

		Node * root;
};

int main() {
	BinarySearchTree<int> tree;

	tree.insert(1);
	tree.insert(3);
}
