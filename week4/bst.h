#ifndef BST_INCLUDED
#define BST_INCLUDED

#include <utility>
#include <iostream>

template <typename T>
class BinarySearchTree
{
	public:
		BinarySearchTree()
			: root(nullptr)
		{};

		~BinarySearchTree()
		{
			this->clear();
		}

		bool insert(const T & object) {
			return this->insert(object, this->root);
		}

		bool contains(const T & object) const {
			return this->contains(object, this->root);
		}

		void remove(const T & object)
		{
			this->remove(object, this->root);
		}

		// In order traversal.
		void print()
		{
			this->print(this->root);
		}

		void clear()
		{
			this->emptyTree(this->root);
		}

		bool empty() const
		{
			return this->root == nullptr;
		}
	private:
		struct Node
		{
			T data;
			Node * left; // Less than
			Node * right; // greater than.

			Node * predecessor;
			Node * successor;

			Node(T data, Node * left = nullptr, Node * right = nullptr)
				: data(data),
				left(left),
				right(right)
			{}
		};

		// * & - Pointer to a reference? Wtf
		bool insert(T object, Node * & root) {
			bool ret = true;

			if ( root == nullptr ) {
				root = new Node(object);
			} else if ( object < root->data ) {
				this->insert(object, root->left);
			} else if ( object > root->data ) {
				this->insert(object, root->right);
			} else { // Duplicate, an error in this implementation.
				ret = false;
			}

			return ret;
		}

		bool contains(const T & object, const Node * root) const
		{
			if ( root == nullptr ) {
				return false;
			} else if ( object < root->data  ) {
				return this->contains(object, root->left);
			} else if ( object > root->data ) {
				return this->contains(object, root->right);
			} else {
				return true; // Match
			}
		}

		void remove(const T & object, Node * & root)
		{
			// We've reached a a leaf without finding the item.
			if ( root == nullptr ) {
				return;
			}

			if ( object < root->data  ) {
				this->remove(object, root->left);
			} else if ( object > root->data ) {
				this->remove(object, root->right);
			} else if ( root->left != nullptr && root->right != nullptr ) { // Two children.
				root->data = this->findMin(root->right)->data;
				this->remove(root->data, root->right);
			} else { // One child.
				Node * old = root;
				root = ( root->left != nullptr ) ? root->left : root->right;
				delete old;
			}
		}

		void print(const Node * node) const
		{
			if ( node == nullptr ) {
				return;
			}

			this->print(node->left);
			std::cout << node->data << "\n";
			this->print(node->right);
		}

		void emptyTree(Node * & root)
		{
			if ( root != nullptr ) { // Base case
				this->emptyTree(root->left);
				this->emptyTree(root->right);
				delete root;
			}

			root = nullptr;
		}

		Node * findMin(Node * root) const
		{
			if ( root == nullptr ) {
				return nullptr;
			}

			// No smaller child, this is the smallest child.
			if ( root->left == nullptr ) {
				return root;
			}

			return this->findMin(root->left);
		}

		Node * root;
};

#endif
