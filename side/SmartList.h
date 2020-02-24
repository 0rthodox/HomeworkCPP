#pragma once

#include <memory>
#include <iostream>

class Node : public std::enable_shared_from_this<Node> {
public:
	std::weak_ptr<Node> parent;
	std::shared_ptr<Node> child;
	int value;
	Node(int val, std::weak_ptr<Node> parent) : value(val){}
	void link(int val) {
		Node n(val, std::enable_shared_from_this<Node>::weak_from_this());
		child = std::make_shared<Node>(n);
	}
};

class SmartList {
public:
	SmartList() : root(0, std::weak_ptr<Node>()) {}
	Node root;
	void add(const int& val) {
		auto currentPtr = & root;
		while(currentPtr->child) {
			currentPtr = currentPtr->child.get();
		}
		currentPtr->link(val);
	}
	void read() {
		auto ptr = &root;
		while (ptr->child) {
			ptr = ptr->child.get();
			std::cout << ptr->value << std::endl;
		}
	}
};