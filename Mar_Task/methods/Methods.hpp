#ifndef METHODS_HPP
#define METHODS_HPP

#include <list>
#include "../include/Point.hpp"
#include "../include/Rectangle.hpp"
#include "../include/Edge.hpp"

List<Edge*> *findContour (Rectangle r[], int n) {
	AxisParallelEdge **schedule = buildSchedule (r, n);
	List<Edge*> *segments = new List<Edge*>;
	Dictionary<AxisParallelEdge*> swepline (axisParallelEdgeCmp);
	Rectangle *sentinel = new Rectangle (Point (-DBL_MAX, -DBL_MAX), Point (DBL_MAX, DBL_MAX), -1);
	sweepline.insert (new AxisParallelEdge(sentinel, BOTTOM_SIDE));

	for (int i = 0; i < 2*n; i++) {
		switch (schedule[i]->type) {
			case LEFT_SIDE:
				schedule[i]->handLeftEdge (sweepline, segments);
				break;
			case RIGHT_SIDE:
				schedule[i]->handleRightEdge (sweepline, segments);
				break;
		}
	}
	return segments;
}


AxisParallelEdge **buildSchedule (Rectangle r[], int n){
	AxisParallelEdge **schedule = new AxisParallelEdgeEdgePtr[2*n];
	for (int i = 0; i < n; i++) {
		schedule[2*i] = new AxisParallelEdge (&r[i], LEFT_SIDE);
		schedule[2*i + 1] = new AxisParallelEdge (&r[i], RIGHT_SIDE);
	}
	insertionSort (schedule, 2*n, axisParallelEdgeCmp);
	return schedule;
}

// comparator
int axisParallelEdgeCmp (AxisParallelEdge *a, AxisParallelEdge *b) {
	if (a->pos() < b->pos()) return -1;
	else if (a->pos() > b->pos()) return 1;
	else if (a->type < b->type) return -1;
	else if (a->type > b->type) return 1;
	else if (a->r->id < b->r->id) return -1;
	else if (a->r->id > b->r->id) return 1;
}


// sort
template <class T>
void insertionSort (T a[], int n, in (*cmp) (T, T)) {
	for (int i = 1; i < n; i++) {
		T v = a[i];
		int j = i;
		while ((j > 0) && ((*cmp) (v, a[j - 1]) < 0)) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = v;
	}
}

#endif
