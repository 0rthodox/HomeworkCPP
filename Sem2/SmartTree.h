#pragma once

#ifndef _SMART_TREE_
#define _SMART_TREE_

#include <memory>
#include <iostream>

template <typename T>
class SmartTree {
	class Node : public std::enable_shared_from_this<Node> {
	public:
		std::weak_ptr<Node> parent;
		std::shared_ptr<Node> lChild;
		std::shared_ptr<Node> rChild;
		bool isRoot;
		T value;

		Node(T val, std::weak_ptr<Node> parent, bool isRoot = 0) : value(val), isRoot(isRoot) {}
		void lLink(T val) {
			Node n(val, std::enable_shared_from_this<Node>::weak_from_this());
			lChild = std::make_shared<Node>(n);
		}
		void rLink(T val) {
			Node n(val, std::enable_shared_from_this<Node>::weak_from_this());
			rChild = std::make_shared<Node>(n);
		}
		void read() {
			if (lChild) {
				lChild->read();
			}
			if (rChild) {
				rChild->read();
			}
			if (!isRoot) {
				std::cout << value << std::endl;
			}
		}
	};
public:
	SmartTree() : root(0, std::weak_ptr<Node>(), 1) {}
	Node root;
	void add(const T& val) {
		auto currentPtr = &root;
		while (1) {
			if (val <= currentPtr->value) {
				if (currentPtr->lChild) {
					currentPtr = currentPtr->lChild.get();
				} else {
					currentPtr->lLink(val);
					break;
				}
			} else {
				if (currentPtr->rChild) {
					currentPtr = currentPtr->rChild.get();
				}
				else {
					currentPtr->rLink(val);
					break;
				}
			}
		}
	}
	void read() {
		root.read();
	}
};

#endif _SMART_TREE_