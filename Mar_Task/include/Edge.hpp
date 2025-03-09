#ifndef EDGES_HPP
#define EDGES_HPP

// sides of rectangle
enum { LEFT_SIDE, RIGHT_SIDE, BOTTOM_SIDE, TOP_SIDE };

class AxisParallelEdge {
	public:
		Rectangle *r;
		int count;
		double m;
		int type; // type of rectangle side from class Side

		AxisParallelEdge (Rectangle *r_, int count_);
		double pos ();
		double min ();
		double max ();
		void setMin ();
		void handleLeftEdge (Dictionary<AxisParallelEdge*>& , List<Edge*>* );
		void handleRightEdge (Dictionary<AxisParallelEdge*>& , List<Edge*>* );
};


AxisParallelEdge::AxisParallelEdge (Rectangle *r_, int count_) :
	r(r_), count(count_)
{
}

double AxisParallelEdge::pos () {
	switch (type) {
		case LEFT_SIDE:
			return r->sw.x;	break;
		case RIGHT_SIDE:
			return r->ne.x;	break;
		case TOP_SIDE:
			return r->ne.y;	break;
		case BOTTOM_SIDE:
			return r->sw.y; break;
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
			segs->append(new Edge (Point (curx, p->pos()), Point (curx, l->pos())));
			segs->append(new Edge (Point (l->min(), l->pos()), Point (curx, l->pos())));
		}
		else if ((l->type == TOP_SIDE) && (l->count++ == 0))
			segs->append(new Edge (Point (l->min(), l->pos()), Point (curx, l->pos())));
	}
	if ((l->count == p->count + 1) == 0)
		segs->append(new Edge (Point (curx, p->pos()), Point (curx, l->pos())));
}


void AxisParallelEdge::handleRightEdge (Dictionary<AxisParallelEdge*> &sweepline, List<Edge*> *segs) {
	AxisParallelEdge uedge (r, TOP_SIDE);
	AxisParallelEdge ledge (r, BOTTOM_SIDE);
	AxisParallelEdge *u = sweepline.find(&uedge);
	AxisParallelEdge *l = sweepline.find(&ledge);
	float curx = pos();
	if (l->count == 1)
		segs->append(new Edge (Point (l->min(), l->pos()), Point (curx, l->pos())));
	if (u->count == 1)
		segs->append(new Edge (Point (u->min(), u->pos()), Point (curx, u->pos())));
	AxisParallelEdge *initl = l;
	AxisParallelEdge *p = l;
	l = sweepline.next();
	for ( ; l != u; p = l, l = sweepline.next()) {
		if ((l->type == BOTTOM_SIDE) && (--l->count == 1)) {
			segs->append(new Edge (Point (curx, p->pos()), Point (curx, l->pos())));
			l->setMin(curx);
		}
		else if ((l->type == TOP_SIDE) && (--l->count == 0))
			l->setMin(curx);
	}
	if (l->count == 0)
		segs->append(new Edge (Point (curx, p->pos()), Point (curx, l->pos())));
	sweepline.remove (u);
	sweepline.remove (initl);
}

#endif
