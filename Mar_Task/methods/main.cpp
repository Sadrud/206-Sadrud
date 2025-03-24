//#include <iostream>
//#include "../include/Data_Structures/Node.cpp"
/*#include "../include/Data_Structures/TreeNode.hpp"
#include "../include/Data_Structures/BraidedNode.hpp"
#include "../include/Data_Structures/Dictionary.hpp"
#include "../include/Data_Structures/List.hpp"
#include "../include/Geometry/Axis_Parallel_Edge.hpp"
#include "../include/Geometry/Rectangle.hpp"
#include "../include/Geometry/Point.hpp"
#include "../include/Geometry/Edge.hpp"
*/
//#include "Methods.hpp"

#include "Methods.hpp"

int cmp (int* a, int* b) {
	if (&a > &b) return 1;
	else if (&a < &b) return -1;
	return 0;
}

int main () {
	Node a;
	Node b;
	Node *c = a.insert(&b);
	std::cout << c << std::endl;

	int *n1 = new int(1);
	TreeNode<int*> a1(n1);

	int *n2 = new int(2);
	BraidedNode<int*> a2(n2);
	int *n3 = new int(3);
	BraidedNode<int*> a3(n3);
	if (a2.next() == nullptr) std::cout << "nullptr" << std::endl;
	if (a2.rchild() != nullptr) std::cout << "nullptr" << std::endl;
	if (a2.rchild() == nullptr) std::cout << a2.rchild() << std::endl;

	std::cout << "rand() = " << rand() << std::endl;

	int *n5 = new int(5);

	RandomizedNode<int*> r(n5);
	if (r.lchild() == nullptr) std::cout << "nulptr" << std::endl;
	if (r.rchild() == nullptr) std::cout << "nulptr" << std::endl;
	if (r.parent() == nullptr) std::cout << "nulptr" << std::endl;
	std::cout << r.priority() << std::endl;

	Dictionary<int*> d(cmp, 1);
	std::cout << d.next() << std::endl;
	std::cout << d.val() << std::endl;

	int *n5n = new int (5);
	d.insert(n5n);
	int *n0 = new int(-1);
	std::cout << *d.locate(n0) << std::endl;
	d.insert(n0);
	int *nn = new int(-5);
	d.insert(nn);
	std::cout << *d.findMin() << std::endl;
	int *n2n = new int(-2);
	d.insert(n2n);
	try {
		d.remove(n0);
	} catch (Exception& ex) { ex.print_message(); }
	std::cout << *d.locate(n0) << std::endl;
	d.remove();

	List<int*> m1;
	std::cout << sizeof(m1) << std::endl;
	int *m2 = new int(10);
	int *m3 = new int(11);
	int *m5 = new int(13);
	int *m4 = new int(12);
	m1.insert(m2);
	std::cout << *m1.val() << std::endl;
	m1.insert(m3);
	std::cout << *m1.val() << std::endl;
	m1.insert(m5);
	std::cout << *m1.val() << std::endl;
	m1.append(m4);
	std::cout << *m1.val() << std::endl;


	List<int*> p1;
	int *p2 = new int(3);
	int *p3 = new int(5);
	p1.insert(p2);
	p1.insert(p3);

	p1.append(&m1);
	std::cout << *p1.val() << std::endl;

	int *p5 = new int(100);
	p1.insert (p5);
	std::cout << *p1.val() << std::endl;

	std::cout << "печать спсиска" << p1.length() << std::endl;
	p1.first();
	for (int i = 0; i < 7; i++) {
		std::cout << *p1.val() << std::endl;
		p1.next();
	}

	Point po1(0, 1);
	Point po2(1, 1);
	Rectangle rect(po1, po2);

	Rectangle* parr = new Rectangle[10];
	for (int i = 0; i < 10; i++) { parr[i] = Rectangle(Point(i, i), Point(i+2, i+2)); }

	List<Edge*>* p = findContour (parr, 2);
	p->print();
	Point poi1(1, 1);
	Point poi2(1, 2);
	Edge* e = new Edge(poi1, poi2);
	e->print();
	p->insert(e);
	delete p;
	delete [] parr;
	return 0;
}
