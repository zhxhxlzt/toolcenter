#include<iostream>
#include <Application.h>
#include <set>
#include <Window.h>
#include <string>
#include <vector>
using namespace std;
using namespace yk;

#include <Delegate.h>
void run(int a)
{
	cout << "run" << a << endl;
}

void say(string name)
{
	cout << "my name is: " << name << endl;
}
class A
{
public:
	A() { cout << "construct A" << endl; }
	A(const A& a) { cout << "copy A" << endl; }
	A(const A&& a) { cout << "move A" << endl; }
};
int main()
{
	/*Delegate<int> dele;
	dele += run;
	dele(20);
	dele -= run;

	Delegate<string> dele2;
	dele2 += say;
	dele2("lyq");
	dele2 -= say;*/

	vector<A> vec;
	auto a = A();
	vec.push_back(a);
	vec.push_back(a);
	vec.push_back(a);

	cout << "test copy ===" << endl;
	for_each(vec.begin(), vec.end(), [](auto v) {});

	cout << "test ref ====" << endl;
	for_each(vec.begin(), vec.end(), [](auto& v) {});
	
	getchar();
	return 0;
}

//	Application app;
//	auto t = make_shared<Timer>();
//	t->timeOut += run;
//	t->start(1000);
//	auto window = make_shared<yk::Window>();
//	window->init();
//
//	auto t2 = make_shared<Timer>();
//	t->timeOut += run;
//
//	while (true)
//	{
//		window->prepare();
//		window->finish();
//	}
//	
//	app.exec();
//	getchar();
//	return 0;
//}