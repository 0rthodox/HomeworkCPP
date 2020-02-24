#pragma once
#include <memory>
#include <iostream>

template <typename Val>
class TreeNode : public std::enable_shared_from_this<TreeNode<Val>> {
public:
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
	std::shared_ptr<TreeNode<Val>> getRight() {
		return right.lock();
	}
	std::shared_ptr<TreeNode<Val>> getLeft() {
		return left.lock();
	}
	bool hasLeft() {
		return(bool(left.lock()));
	}
	bool hasRight() {
		return(bool(right.lock()));
	}
	~TreeNode() {
		std::cout << "Destructing node" << std::endl;
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
	std::shared_ptr<TreeNode<Val>> top;
public:
	BinaryTree() : size(0), {}
	~BinaryTree() {
		std::cout << "Destructing tree" << std::endl;
	}
	void add(Val value) {
		TreeNode<Val> newNode(value);
		std::shared_ptr<TreeNode<Val>> newShared(&newNode);
		if (size++) {
			link(top, newShared);
		} else {
			top = newShared;
		}
	}

private:
	void link(std::shared_ptr<TreeNode<Val>> parent, std::shared_ptr<TreeNode<Val>> child) {
		if (child->getValue() <= parent->getValue()) {
			if (parent->hasLeft()) {
				link(parent->getLeft(), child);
			} else {
				parent->setLeft(child);
			}
		}
		else if (child->getValue() > parent->getValue()) {
			if (parent->hasRight()) {
				link(parent->getRight(), child);
			}
			else {
				parent->setRight(child);				
			}
		}
	}
};