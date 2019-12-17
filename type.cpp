#include "stdafx.h"
#include "type.h"
#include "type_point.h"

namespace Contour
{
	Point3::Point3()
	{

	}
	Point3::Point3(double x, double y, double z) : x_(x), y_(y), z_(z)
	{
	}

	Point3::Point3(double pos[3]) : x_(pos[0]), y_(pos[1]), z_(pos[2])
	{
	}
	Triangle::Triangle()
	{

	}
	Triangle::Triangle(Pro3dPnt p1, Pro3dPnt p2, Pro3dPnt p3, ProVector v1)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		normals = v1;
	}
	Triangle::~Triangle()
	{

	}
	Triangle2::Triangle2()
	{

	}
	Triangle2::~Triangle2()
	{

	}
	Triangle2::Triangle2(Point2 p1, Point2 p2, Point2 p3)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
	}
	void Triangle2::getAABB(double min[2], double max[2])
	{
		min[0] = min(min(points[0].x, points[1].x), points[2].x);
		min[1] = min(min(points[0].y, points[1].y), points[2].y);
		max[0] = max(max(points[0].x, points[1].x), points[2].x);
		max[1] = max(max(points[0].y, points[1].y), points[2].y);
		return;
	}
	void Triangle2::GetPnts(Point2 out_points[3])
	{
		out_points[0] = points[0];
		out_points[1] = points[1];
		out_points[2] = points[2];
	}
	bool Triangle2::isOnTriangle(const Point2& pnt)
	{
		double min[2], max[2];
		getAABB(min,max);
		if (pnt.x<min[0] || pnt.x>max[0] || pnt.y<min[1] || pnt.y>max[1])
		{
			return false;
		}
		int cross_count = 0;

		for (int i = 0; i < 3; ++i) {
			Point2 p1 = points[i];
			Point2 p2 = points[(i + 1) % 3];
			if (p1.y == p2.y)
				continue;        /// 跳过水平边

			if (pnt.y < min(p1.y, p2.y))
				continue;        /// 点低于线段，跳过

			if (pnt.y >= max(p1.y, p2.y))
				continue;        /// 点高于线段, 跳过

			double x = (pnt.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
			if (x > pnt.x)
				cross_count++;
		}

		if (cross_count % 2 == 1)
			return true;

		if (onSegment(pnt, points[0], points[1]) || onSegment(pnt, points[1], points[2]) ||
			onSegment(pnt, points[2], points[0]))
			return true;

		return false;
	}
	Triangle2 Triangle::to2D()
	{
		Point2 p1, p2, p3;
		p1.x = points[0].x();
		p1.y = points[0].y();
		p2.x = points[1].x();
		p2.y = points[1].y();
		p3.x = points[2].x();
		p3.y = points[2].y();
		return Triangle2(p1, p2, p3);
	}
}
