#include<iostream>
#include "Object.h"
#include "World.h"
#include <set>

using namespace std;

//int main()
//{
//	Object o;
//	o.func1();
//	o.func2();
//	cout << o.className() << endl;
//	cout << o.baseClassName() << endl;
//
//	World w;
//	cout << w.className() << endl;
//	cout << w.baseClassName() << endl;
//	getchar();
//	return 0;
//}
int main()
{
	set<int> ins = { 1, 5, 34, 2, 9, 0 };

	for (auto it = ins.begin(); it != ins.end();)
	{
		if (*it < 10)
		{
			auto last = it++;
			ins.erase(last);
		}
		else
			it++;
	}

	for (auto &e : ins)
		cout << e << endl;
	getchar();
	return 0;
}