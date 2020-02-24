#pragma once
#include <memory>
#include <iostream>
#include <vector>

template <typename Val>
class TreeNode : public std::enable_shared_from_this<TreeNode<Val>> {
public:
	TreeNode() {}
	TreeNode(const Val & value) : value(value) {}
	void setParent(std::shared_ptr<TreeNode<Val>> parent) {
		this->parent = parent;
	}
	void setRight(std::shared_ptr<TreeNode<Val>> child) {
		child->setParent(std::enable_shared_from_this<TreeNode<Val>>::shared_from_this());
		right = child;

	}
	void setLeft(std::shared_ptr<TreeNode<Val>> child) {
		child->setParent(std::enable_shared_from_this<TreeNode<Val>>::shared_from_this());
		left = child;
	}
	Val getValue() {
		return value;
	}
	void setValue(Val newValue) {
		value = newValue;
	}
	TreeNode<Val> * getRight() {
		return right.lock().get();
	}
	TreeNode<Val> * getLeft() {
		return left.lock().get();
	}
	bool hasLeft() {
		return(bool(left.lock()));
	}
	bool hasRight() {
		return(bool(right.lock()));
	}
	~TreeNode() {
		std::cout << "Destructing node with value = " << value << std::endl;
	}
	void link(std::shared_ptr<TreeNode<Val>> child) {
		if (child->getValue() <= getValue()) {
			if (hasLeft()) {
				getLeft()->link(child);
			}
			else {
				setLeft(child);
			}
		}
		else {
			if (hasRight()) {
				getRight()->link(child);
			}
			else {
				setRight(child);
			}
		}
	}
private:
	std::shared_ptr<TreeNode<Val>> parent;
	std::weak_ptr<TreeNode<Val>> right;
	std::weak_ptr<TreeNode<Val>> left;
	Val value;
};

template <typename Val>
class BinaryTree {
private:
	int size;
	std::vector<std::shared_ptr<TreeNode<Val>>> ptrs;
	std::vector<TreeNode<Val>> vals;
public:
	BinaryTree() : size(0) {}
	~BinaryTree() {
		std::cout << "Destructing tree" << std::endl;
	}
	void add(const Val & value) {
		std::cout << "Adding value " << value << std::endl;
		vals.push_back(TreeNode<Val>(value));
		ptrs.push_back(std::shared_ptr<TreeNode<Val>>(&(vals.back())));
		/*if (size++) {
			ptrs[0]->link(ptrs.back());
		}*/
		std::cout << "top value = " << ptrs[0]->getValue() << std::endl;
		std::cout << "shared pointers: " << ptrs.size() << std::endl;
		std::cout << "values: " << vals.size()  << "\n" << std::endl;
	}
};