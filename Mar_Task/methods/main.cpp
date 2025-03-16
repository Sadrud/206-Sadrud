#include <iostream>
#include <list>
#include <cfloat>
#include "../include/Data_Structures/Node.hpp"
#include "../include/Data_Structures/TreeNode.hpp"
#include "../include/Data_Structures/BraidedNode.hpp"
#include "../include/Data_Structures/RandomizedNode.hpp"
#include "../include/Data_Structures/Dictionary.hpp"
#include "../include/Geometry/Axis_Parallel_Edge.hpp"
#include "../include/Geometry/Rectangle.hpp"
#include "../include/Geometry/Point.hpp"

int cmp (int a, int b) {
	if (a > b) return 1;
	else if (a < b) return -1;
	return 0;
}

int main () {
	Node a;
	Node b;
	Node *c = a.insert(&b);
	std::cout << c << std::endl;

	TreeNode<int> a1(1);

	BraidedNode<int> a2(2);
	BraidedNode<int> a3(3);
	if (a2.next() == nullptr) std::cout << "nullptr" << std::endl;
	if (a2.rchild() != nullptr) std::cout << "nullptr" << std::endl;
	if (a2.rchild() == nullptr) std::cout << a2.rchild() << std::endl;

	std::cout << "rand() = " << rand() << std::endl;

	RandomizedNode<int> r(5);
	if (r.lchild() == nullptr) std::cout << "nulptr" << std::endl;
	if (r.rchild() == nullptr) std::cout << "nulptr" << std::endl;
	if (r.parent() == nullptr) std::cout << "nulptr" << std::endl;
	std::cout << r.priority() << std::endl;

	Dictionary<int> d(cmp, 1);
	std::cout << d.next() << std::endl;
	std::cout << d.val() << std::endl;

	d.insert(5);
	std::cout << d.locate(-1) << std::endl;
	d.insert(1);
	d.insert(-5);
	std::cout << d.findMin() << std::endl;
	d.insert(-2);
	try {
		d.remove(-1);
	} catch (Exception& ex) { ex.print_message(); }
	std::cout << d.locate(-1) << std::endl;
	d.remove();

	return 0;
}
