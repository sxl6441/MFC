#include "stdafx.h"
#include "FPCBaseMath.h"


bool SortEdges(IN const list<UniqueLine>& list_lines2,
	OUT list<list<UniqueLine>>& complete_ring, OUT  list<list<UniqueLine>>& uncomplete_lines)
{
	typedef map<UniqueLine, int>::iterator IT;
	complete_ring.resize(0);
	uncomplete_lines.resize(0);
	if (list_lines2.size() == 0) {
		return false;
	}
	//采用最小环算法，得到最小环即止步
	list<UniqueLine> list_lines = list_lines2;
	int max_cycle_cnt = (int)(list_lines.size()*list_lines.size());//最大循环次数


	list<UniqueLine> vec_store;

	UniquePt st_pt = list_lines.front().end1;//搜寻点，刚开始设置为第一个线的end1

	while (list_lines.size() != 0 && max_cycle_cnt > 0) {
		max_cycle_cnt--;
		bool find = false;

		list<UniqueLine>::iterator iter = list_lines.begin();
		for (; iter != list_lines.end(); ++iter) {
			if (iter->end1 == st_pt) {
				find = true;
				st_pt = iter->end2;
				vec_store.push_back(*iter);
				list_lines.erase(iter);
				break;
			}
			else if (iter->end2 == st_pt) {
				find = true;
				st_pt = iter->end1;
				//换位置
				UniquePt temp = iter->end1;
				iter->end1 = iter->end2;
				iter->end2 = temp;

				vec_store.push_back(*iter);
				list_lines.erase(iter);
				break;
			}
		}

		if (find == false) {//说明找不到下一个点了
							//判断vec_store的首点与尾点是否相同
			if (vec_store.front().end1 == vec_store.back().end2) {
				complete_ring.push_back(vec_store);
			}
			else {
				uncomplete_lines.push_back(vec_store);
			}
			vec_store.resize(0);
			if (list_lines.size() > 0) {
				st_pt = list_lines.front().end1;
			}
		}
	}
	//判断vec_store的首点与尾点是否相同
	if (vec_store.front().end1 == vec_store.back().end2) {
		complete_ring.push_back(vec_store);
	}
	else {
		uncomplete_lines.push_back(vec_store);
	}
	return true;
}
void DelSmallSegment(list<UniqueLine>&lines, double minlength)
{
	typedef list<UniqueLine>::iterator IT;
	for (IT iter = lines.begin(); iter != lines.end(); ++iter) {
		double len = iter->GetLength();
		if (len <= minlength) {
			IT iter2 = iter; iter2++;
			if (iter2 == lines.end()) { iter2 = lines.begin(); }
			iter->end2 = iter2->end2;
			lines.erase(iter2);
		}
	}
	return;
}

bool  FindSTLBoundary(IN vector<Triangle>&triangles,
	OUT vector<Point3>&outer_boundary, OUT vector<vector<Point3>>&inner_boundary)
{
	//排重+排序
	if (triangles.size() == 0) { return false; }
	outer_boundary.resize(0);
	inner_boundary.resize(0);

	map<UniqueLine, int> map_lines;
	Point3 ptx[3];
	for (int i = 0; i < (int)triangles.size(); i++) {
		triangles[i].GetPnts(ptx);
		UniquePt tp[3] = { ptx[0],ptx[1],ptx[2] };
		for (int j = 0; j < 3; j++) {
			UniqueLine temp(tp[j], tp[(j + 1) % 3]);
			map<UniqueLine, int>::iterator iter = map_lines.find(temp);
			if (iter != map_lines.end()) {
				map_lines.erase(iter);
			}
			else {
				map_lines.insert(make_pair(temp, 0));
			}
		}
	}
	//此时已经是多条边界线段了
	list<UniqueLine> lines;
	for (map<UniqueLine, int>::iterator iter = map_lines.begin(); iter != map_lines.end(); ++iter) {
		lines.push_back(iter->first);
	}
	list<list<UniqueLine>> complete_ring;
	list<list<UniqueLine>> uncomplete_lines;//不完整的环废弃不用
	SortEdges(lines, complete_ring, uncomplete_lines);

	if (complete_ring.size() == 0) {
		return false;
	}

	//找到环长最长的当做外边界======这个条件90%的情况应该是正确的
	typedef list<list<UniqueLine>>::iterator IT_LIST_LIST;
	typedef list<UniqueLine>::iterator IT_LIST;

	IT_LIST_LIST max_len_index;

	double max_len = 0;
	for (IT_LIST_LIST iter = complete_ring.begin(); iter != complete_ring.end(); ++iter) {
		DelSmallSegment(*iter,0.5);//去除小线段

		double sum_len = 0;
		for (IT_LIST iter_a = iter->begin(); iter_a != iter->end(); ++iter_a) {
			sum_len += iter_a->GetLength();
		}
		if (sum_len > max_len) {
			max_len_index = iter;
			max_len = sum_len;
		}
	}

	for (IT_LIST iter_a = max_len_index->begin(); iter_a != max_len_index->end(); ++iter_a) {
		outer_boundary.push_back(iter_a->end1.pt);
	}
	for (IT_LIST_LIST iter = complete_ring.begin(); iter != complete_ring.end(); ++iter) {
		if (iter == max_len_index) { continue; }

		vector<Point3> temp;
		for (IT_LIST iter_a = iter->begin(); iter_a != iter->end(); ++iter_a) {
			temp.push_back(iter_a->end1.pt);
		}
#if 1
		std::reverse(temp.begin(), temp.end());
#endif
		inner_boundary.push_back(temp);
	}
	return true;
}
bool  TransSTLToPointCloud(IN vector<Triangle>&triangles,
	OUT vector<Point3>&point_cloud)
{
	point_cloud.resize(0);
	if (triangles.size() == 0) { return false; }
	map<UniquePt, int> map_pts;
	Point3 ptx[3];
	for (int i = 0; i < (int)triangles.size(); i++) {
		triangles[i].GetPnts(ptx);
		map_pts.insert(make_pair(UniquePt(ptx[0]), 0));
		map_pts.insert(make_pair(UniquePt(ptx[1]), 0));
		map_pts.insert(make_pair(UniquePt(ptx[2]), 0));
	}
	point_cloud.reserve(map_pts.size());
	for (map<UniquePt, int>::iterator iter = map_pts.begin(); iter != map_pts.end(); ++iter) {
		point_cloud.push_back(iter->first.pt);
	}
	return true;
}
