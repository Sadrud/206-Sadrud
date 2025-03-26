#include "Axis_Parallel_Edge.hpp"

AxisParallelEdge::AxisParallelEdge (Rectangle *r_, int type_) :
	r(r_), count(0), m(-DBL_MAX), type(type_)
{
}

void AxisParallelEdge::print() const {
	if (!r) {
		std::cout << "Rectangle is nullptr!" << std::endl;
		return;
	}

	switch (type) {
		case LEFT_SIDE:
			std::cout << "LEFT_SIDE ";
			std::cout << "(" << r->sw.x << ", " << r->sw.y << ") -> ("
				<< r->sw.x << ", " << r->ne.y << ")" << std::endl;
			break;
		case RIGHT_SIDE:
			std::cout << "RIGHT_SIDE ";
			std::cout << "(" << r->ne.x << ", " << r->sw.y << ") -> ("
				<< r->ne.x << ", " << r->ne.y << ")" << std::endl;
			break;
		case BOTTOM_SIDE:
			std::cout << "BOTTOM_SIDE ";
			std::cout << "(" << r->sw.x << ", " << r->sw.y << ") -> ("
				<< r->ne.x << ", " << r->sw.y << ")" << std::endl;
			break;
		case TOP_SIDE:
			std::cout << "TOP_SIDE ";
			std::cout << "(" << r->sw.x << ", " << r->ne.y << ") -> ("
				<< r->ne.x << ", " << r->ne.y << ")" << std::endl;
			break;
		default:
			std::cout << "UNKNOWN_SIDE" << std::endl;
			break;
	}
}

double AxisParallelEdge::pos () {
	switch (type) {
		case LEFT_SIDE:
			return r->sw.x;
		case RIGHT_SIDE:
			return r->ne.x;
		case TOP_SIDE:
			return r->ne.y;
		case BOTTOM_SIDE:
		default:
			return r->sw.y;
	}
}

double AxisParallelEdge::min () {
	if (m > -DBL_MAX)
		return m;
	switch (type) {
		case LEFT_SIDE:
		case RIGHT_SIDE:
			return r->sw.y; break;
		case TOP_SIDE:
		case BOTTOM_SIDE:
		default:
			return r->sw.x; break;
	}
}

double AxisParallelEdge::max () {
	switch (type) {
		case LEFT_SIDE:
		case RIGHT_SIDE:
			return r->ne.y; break;
		case TOP_SIDE:
		case BOTTOM_SIDE:
		default:
			return r->ne.x; break;
	}
}

void AxisParallelEdge::setMin (double f) {
	m = f;
}

void AxisParallelEdge::handleLeftEdge (Dictionary<AxisParallelEdge*> &sweepline, List<Edge*> *segs) {
	sweepline.insert (new AxisParallelEdge (r, TOP_SIDE));
	AxisParallelEdge *u = sweepline.val();
	sweepline.insert (new AxisParallelEdge (r, BOTTOM_SIDE));
	AxisParallelEdge *l = sweepline.val();
	AxisParallelEdge *p = sweepline.prev();
	float curx = pos();
	l->count = p->count + 1;
	p = sweepline.next();
	l = sweepline.next();
	for ( ; l != u; p = l, l = sweepline.next()) {
		if ((l->type == BOTTOM_SIDE) && (l->count++ == 1)) {
			Point a (curx, p->pos());
			Point b (curx, l->pos());
			segs->insert(new Edge (a, b));
			Point c (l->min(), l->pos());
			Point d (curx, l->pos());
			segs->insert(new Edge (c, d));
		}
		else if ((l->type == TOP_SIDE) && (l->count++ == 0)) {
			Point a (l->min(), l->pos());
			Point b (curx, l->pos());
			segs->insert(new Edge (a, b));
		}
	}
	if ((l->count = p->count - 1) == 0) {
		Point a (curx, p->pos());
		Point b (curx, l->pos());
		segs->insert(new Edge (a, b));
	}
}


void AxisParallelEdge::handleRightEdge (Dictionary<AxisParallelEdge*> &sweepline, List<Edge*> *segs) {
	AxisParallelEdge uedge (r, TOP_SIDE);
	AxisParallelEdge ledge (r, BOTTOM_SIDE);
	AxisParallelEdge *u = sweepline.find(&uedge);
	AxisParallelEdge *l = sweepline.find(&ledge);
	float curx = pos();
	if (l->count == 1) {
		Point a(l->min(), l->pos());
		Point b(curx, l->pos());
		segs->append(new Edge (a, b));
	}
	if (u->count == 0) {
		Point a (u->min(), u->pos());
		Point b (curx, u->pos());
		segs->append(new Edge (a, b));
	}
	AxisParallelEdge *initl = l;
	AxisParallelEdge *p = l;
	l = sweepline.next();
	for (int i = 0; l != u; p = l, l = sweepline.next()) {
		if ((l->type == BOTTOM_SIDE) && (--l->count == 1)) {
			Point a(curx, p->pos());
			Point b(curx, l->pos());
			segs->append(new Edge (a, b));
			l->setMin(curx);
		}
		else if ((l->type == TOP_SIDE) && (--l->count == 0))
			l->setMin(curx);
	}
	if (l->count == 0) {
		Point a (curx, p->pos());
		Point b (curx, l->pos());
		segs->append(new Edge (a, b));
	}
	sweepline.remove (u);
	sweepline.remove (initl);
}
