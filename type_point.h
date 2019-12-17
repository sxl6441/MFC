#pragma once
namespace Contour
{
#ifdef MIN
#undef MIN
#endif
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#ifdef MAX
#undef MAX
#endif
#define MAX(x, y) ((x) > (y) ? (x) : (y))

	/// 二维点
	struct Point2
	{
		double x, y;
		bool flag;
		bool operator==(_In_ Point2 point) const throw()
		{
			return (x == point.x && y == point.y);
		}
		Point2(double x1, double y1)
		{
			flag = false;
			x = x1;
			y = y1;
		}
		Point2()
		{
			flag = false;
		}
	};

	/// 判断点是否在线段上
	inline bool onSegment(const Point2& pnt, const Point2& start, const Point2& end)
	{
		if ((pnt.x < MIN(start.x, end.x)) || (pnt.x > MAX(start.x, end.x)) ||
			(pnt.y < MIN(start.y, end.y)) || (pnt.y > MAX(start.y, end.y)))
			return false;

		if (abs((pnt.x - start.x) * (end.y - start.y) - (end.x - start.x) * (pnt.y - start.y)) < 1.0e-6)
			return true;
		return false;
	}

	/// 三维点
	class Point3
	{
	public:
		Point3();
		Point3(double x, double y, double z);
		Point3(double pos[3]);

		double x() const { return x_; }
		double y() const { return y_; }
		double z() const { return z_; }

	private:
		double x_, y_, z_;
	};
}
