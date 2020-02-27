#pragma once

#ifndef _SMART_TREE_
#define _SMART_TREE_

#include <memory>
#include <iostream>

template <typename T>
class SmartTree {
	class Node : public std::enable_shared_from_this<Node> {
		T value;
		std::weak_ptr<Node> parent;
		bool isRoot;
		std::shared_ptr<Node> lChild;
		std::shared_ptr<Node> rChild;
	public:
		const T getValue() const {
			return value;
		}
		std::shared_ptr<Node> getLChild() {
			return lChild;
		}
		std::shared_ptr<Node> getRChild() {
			return rChild;
		}

		Node(const T& val, std::weak_ptr<Node> parent, bool isRoot = 0) : value(val), isRoot(isRoot) {}
		void lLink(const T& val) {
			Node n(val, std::enable_shared_from_this<Node>::weak_from_this());
			lChild = std::make_shared<Node>(n);
		}
		void rLink(const T& val) {
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
		~Node() = default;
	};
private:
	Node root;
public:
	SmartTree() : root(0, std::weak_ptr<Node>(), 1) {}
	void add(const T& val) {
		auto currentPtr = &root;
		while (1) {
			if (val <= currentPtr->getValue()) {
				if (currentPtr->getLChild()) {
					currentPtr = currentPtr->getLChild().get();
				} else {
					currentPtr->lLink(val);
					break;
				}
			} else {
				if (currentPtr->getRChild()) {
					currentPtr = currentPtr->getRChild().get();
				}
				else {
					currentPtr->rLink(val);
					break;
				}
			}
		}
	}
	void read() {
		std::cout << "Tree contains: " << "\n";
		root.read();
		std::cout << std::endl;
	}
	~SmartTree() = default;
};

#endif _SMART_TREE_