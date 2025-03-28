#include "Methods.hpp"

int axisParallelEdgeCmp (AxisParallelEdge *a, AxisParallelEdge *b) {
	if (a->pos() < b->pos()) return -1;
	else if (a->pos() > b->pos()) return 1;
	else if (a->type < b->type) return -1;
	else if (a->type > b->type) return 1;
	else if (a->r->id < b->r->id) return -1;
	else if (a->r->id > b->r->id) return 1;
	return 0;
}


template <class T>
void insertionSort (T a[], int n, int (*cmp) (T, T)) {
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


AxisParallelEdge **buildSchedule (Rectangle r[], int n){
	AxisParallelEdge **schedule = new AxisParallelEdge*[2*n];
	for (int i = 0; i < n; i++) {
		schedule[2*i] = new AxisParallelEdge (&r[i], LEFT_SIDE);
		schedule[2*i + 1] = new AxisParallelEdge (&r[i], RIGHT_SIDE);
	}
	insertionSort (schedule, 2*n, axisParallelEdgeCmp);
	return schedule;
}

extern "C" {
	List<Edge*>* findContour (Rectangle r[], int n) {
		AxisParallelEdge **schedule = buildSchedule (r, n);
		List<Edge*> *segments = new List<Edge*>;
		Dictionary<AxisParallelEdge*> swepline (axisParallelEdgeCmp, -1);
		Rectangle *sentinel = new Rectangle (Point (-DBL_MAX/2, -DBL_MAX/2), Point (DBL_MAX/2, DBL_MAX/2), -1);
		swepline.insert (new AxisParallelEdge(sentinel, BOTTOM_SIDE));

		for (int i = 0; i < 2*n; i++) {
			while (!swepline.isHead()) {
				swepline.next();
			}
			switch (schedule[i]->type) {
				case LEFT_SIDE:
					schedule[i]->handleLeftEdge (swepline, segments);
					break;
				case RIGHT_SIDE:
					schedule[i]->handleRightEdge (swepline, segments);
					break;
			}
		}
		for (int i = 0; i < 2*n; i++){ delete schedule[i]; }
		delete [] schedule;
		delete sentinel;
		return segments;
	}
}
