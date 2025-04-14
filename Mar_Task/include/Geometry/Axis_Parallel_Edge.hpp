#ifndef AXIS_PARALLEL_EDGE_HPP
#define AXIS_PARALLEL_EDGE_HPP

#include "Rectangle.hpp"
#include <cmath>
#include <cfloat>
#include <limits>
#include "Edge.hpp"
#include "../Data_Structures/List.hpp"
#include "../Data_Structures/Dictionary.hpp"

enum { LEFT_SIDE, RIGHT_SIDE, BOTTOM_SIDE, TOP_SIDE };

class AxisParallelEdge {
	public:
		Rectangle *r;
		int count;
		double m;
		int type = 1; // type of rectangle side from class Side

		AxisParallelEdge () : r(new Rectangle(Point(0, 0), Point(0, 0))), count(0), type(-1) {}
		~AxisParallelEdge () {}
		AxisParallelEdge (Rectangle *r_, int count_);
		double pos ();
		double min ();
		double max ();
		void setMin (double);
		void handleLeftEdge (Dictionary<AxisParallelEdge*>& , List<Edge*>* );
		void handleRightEdge (Dictionary<AxisParallelEdge*>& , List<Edge*>* );

		void print () const;
};

#endif
