#include "sharepointer.h"
#include<vector>
using namespace std;
vector<int> spl;
template<class T>
sharepointer<T>::sharepointer(T b)
{
	a = b;
	contador = 1;
	cual = spl.size();
	spl.push_back(1);
}
template<class T>
sharepointer<T>::sharepointer(sharepointer &p) {
	cual = p.cual;
	spl[cual] += 1;
}
template<class T>
int sharepointer<T>::conta() {
	return spl[cual];
}
sharepointer<int>::~sharepointer()
{
}
