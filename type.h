#pragma once

#include <vector>
#include <ProSurface.h>
#include "type_point.h"

namespace Contour
{
	const double EPS5 = 1.0e-5;

	enum Axis
	{
		AXISX,
		AXISY,
		AXISZ
	};

	class Triangle2
	{
	public:
		Triangle2();
		~Triangle2();
		Triangle2(Point2 p1, Point2 p2, Point2 p3);

		/// 获取三角形的包围盒
		void getAABB(double min[2], double max[2]);
		/// 判断点是否在三角形上
		bool isOnTriangle(const Point2& pnt);
		//返回点
		void  GetPnts(Point2 out_points[3]);
	private:
		Point2 points[3];
	};

	class Triangle
	{
	public:
		Triangle();
		Triangle(Pro3dPnt p1, Pro3dPnt p2, Pro3dPnt p3, ProVector v1);
		//Triangle(Point3 p1, Point3 p2, Point3 p3)
		//	: points{ p1, p2, p3 }
		//{ }
		~Triangle();
		Triangle2 to2D();    // x==0 沿x轴投影，x==1 沿y轴投影, x==2 沿z轴投影
		void GetNormal(Point3&nor)
		{
			memcpy(&nor,&normals, sizeof(Point3));
		}
		//返回点
		void  GetPnts(Point3 out_points[3])
		{
			memcpy(out_points, points, sizeof(double[3])*3);
		}
	private:
		Point3 points[3];//点
		Point3 normals;//向量
	};
}
