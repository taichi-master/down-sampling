#include <iostream>
#include <map>
#include <set>
#include <functional>
#include "include/modal.h"

using namespace std;

uint modal (int size, uint arr[]) {
  map<uint, uint> bucket;

  for (uint i = 0; i < size; i++)
    bucket[arr[i]]++;

	typedef function<bool(pair<uint, uint>, pair<uint, uint>)> Comparator;

	Comparator compFunctor =
  	[](pair<uint, uint> el_1, pair<uint, uint> el_2) {
  		return el_1.second > el_2.second;
  	};

	set<pair<uint, uint>, Comparator> sorted_bucket(
		bucket.begin(), bucket.end(), compFunctor);

  uint value;
  for (pair<uint, uint> el : sorted_bucket) {
    value = el.first;
    break;
  }

  return value;
}
