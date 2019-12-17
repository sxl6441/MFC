#pragma once
#include"type.h"
#include<map>
#include<list>
#include<vector>
using namespace std;
using namespace Contour;
struct UniquePt //用来排重 点的类
{
	Point3 pt;
	UniquePt() :pt(0, 0, 0) {}
	UniquePt(double x, double y, double z) :pt(x, y, z) {}
	UniquePt(const Point3 &p3d) :pt(p3d) {}
	bool operator<(const UniquePt&b) const {
		if (b.pt.x() - pt.x()> EPS5) {
			return true;
		}
		else if (pt.x() - b.pt.x() > EPS5) {
			return false;
		}
		else {//X相等
			if (b.pt.y() - pt.y() > EPS5) {
				return true;
			}
			else if (pt.y() - b.pt.y() > EPS5) {
				return false;
			}
			else {//X和Y相等
				if (b.pt.z() - pt.z() > EPS5) {
					return true;
				}
				else if (pt.z() - b.pt.z() > EPS5) {
					return false;
				}
				else {//X和Y和Z相等
					return false;//======核心，保证换位置仍为false
				}
			}
		}
	}
	bool operator==(const UniquePt&b) const {
		return abs(b.pt.x() - pt.x()) < EPS5&&abs(b.pt.y() - pt.y()) < EPS5&&abs(b.pt.z() - pt.z()) < EPS5;
		//也可以 *this<b && b<*this;
	}
};


struct UniqueLine {//用来排重 线的类
	UniquePt end1;
	UniquePt end2;
	UniqueLine() {}
	UniqueLine(UniquePt end1_, UniquePt end2_) {
		if (end1_ < end2_) {
			end1 = end1_; end2 = end2_;
		}
		else {
			end1 = end2_; end2 = end1_;
		}
	}
	bool operator<(const UniqueLine&b) const {
		if (end1 < b.end1) {
			return true;
		}
		else if (b.end1 < end1) {
			return false;
		}
		else {
			if (end2 < b.end2) {
				return true;
			}
			else if (b.end2 < end2) {
				return false;
			}
			else {//两条线相等
				return false;//======核心，保证换位置仍为false
			}
		}
	}
	double GetLength() {
		const Point3&p1 = end1.pt;
		const Point3&p2 = end2.pt;
		double square = pow((p1.x() - p2.x()), 2) + pow((p1.y() - p2.y()), 2) + pow((p1.z() - p2.z()), 2);
		return sqrt(square);
	}
};



bool  TransSTLToPointCloud(IN vector<Triangle>&triangles,
	OUT vector<Point3>&point_cloud);

//triangles:从STL面文件读取到的三角形
//outer_boundary:最外面的边界环
//inner_boundary:内部的多个边界环
bool  FindSTLBoundary(IN vector<Triangle>&triangles,
	OUT vector<Point3>&outer_boundary, OUT vector<vector<Point3>>&inner_boundary);

void DelSmallSegment(list<UniqueLine>&lines, double minlength = 0.2);

bool SortEdges(IN const list<UniqueLine>& list_lines2,
	OUT list<list<UniqueLine>>& complete_ring, OUT  list<list<UniqueLine>>& uncomplete_lines);
