/*!
********************************************************
*	@file TransValues.cpp
*	@author Kalikin D.M.
*	@date   02.02.2023
*	@brief Реализация файла TransValues.h
**********************************************************
*/

#include "LIDPacker/maker/Brain/TransValues.h"


TransValues::TransValues(std::vector<QString> oldA, std::vector<QString> newA) :
	prOrd(oldA), crOrd(newA) {

}
TransValues::~TransValues() {
	tmpxyVal.clear();
}
std::multimap<int, std::vector<int>>  TransValues::swap_args() {
	std::vector<QString>::iterator it_prev, it_curr;
	std::vector<int> new_tmp;
	std::multimap<int, std::vector<int> > sw_strokTab;
	int key = 0;
	for (it_strokTab = strokTab.begin(); it_strokTab != strokTab.end(); ++it_strokTab) {
		int k = 0, b = 0, tmp = 0;
		it_curr = crOrd.begin();
		new_tmp.clear();
		for (it_prev = prOrd.begin(); it_prev != prOrd.end(); ++it_prev) {
			for (b = 0; it_curr != crOrd.end(); ++it_curr) {
				if (*it_prev == *it_curr) {
					new_tmp.push_back(it_strokTab->second[b]);
				}
				b++;
			}
			it_curr = crOrd.begin();
			++k;
		}
		sw_strokTab.insert(std::make_pair(key, new_tmp));
		key ++ ;
	}
	return sw_strokTab;
}
const void TransValues::get_strk_args(std::vector<int> ar, int i) {
    
	strokTab.insert(std::make_pair(i, ar));
}
const void TransValues::get_clmn_args(int j) {
	strokTab = swap_args();
	colmnTab.insert(std::make_pair(j, strokTab));
	strokTab.clear();
}
std::vector<std::vector<sreal_t>> TransValues::get_new_arr(std::vector<int>allord, std::vector<int> siz,
	std::vector<std::vector<sreal_t>> xyVal) {
	Dimensions* trn = new Dimensions(allord, siz);
	std::vector<int> xy;	int sdvig = allord.size() - 1;
	it_Tab = colmnTab.begin();
	it_strokTab = it_Tab->second.begin();
	int l = it_Tab->second.size();
	sreal_t tmp;
	tmpxyVal.clear();
	tmpxyVal.resize(l);

	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < colmnTab.size(); ++j) {
			it_Tab = colmnTab.find(j);
			it_strokTab = it_Tab->second.find(i);
			xy = trn->XYByArgs(it_strokTab->second);
			tmp = xyVal[xy[1]][xy[0]];
			tmpxyVal[i].push_back(tmp);
		}
	}

	delete trn;

	xy.clear();

	return tmpxyVal;
}