#ifndef NETHODS_HPP
#define METHODS_HPP

#include "../include/Data_Structures/Node.hpp"
#include "../include/Geometry/Axis_Parallel_Edge.hpp"
#include "../include/Geometry/Edge.hpp"

static double min = -DBL_MAX;
static double max = DBL_MAX;

int axisParallelEdgeCmp (AxisParallelEdge *a, AxisParallelEdge *b);
template <class T>
void insertionSort (T a[], int n, int (*cmp) (T, T));
AxisParallelEdge **buildSchedule (Rectangle r[], int n);
List<Edge*>* findContour (Rectangle r[], int n);

#endif
