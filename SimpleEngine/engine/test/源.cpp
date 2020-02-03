#include<iostream>
#include <Application.h>
#include <set>
#include <Window.h>
using namespace std;
using namespace yk;
void run()
{
	cout << "run" << endl;
}

int main()
{
	Application app;
	auto t = make_shared<Timer>();
	t->timeOut += run;
	t->start(1000);
	auto window = make_shared<yk::Window>();
	window->init();

	while (true)
	{
		window->prepare();
		window->finish();
	}
	
	app.exec();
	getchar();
	return 0;
}