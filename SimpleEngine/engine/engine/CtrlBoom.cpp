#include "CtrlBoom.h"
#include "GameObject.h"
using namespace yk;


void CtrlBoom::Update()
{
	auto progress = fmod(glfwGetTime(), 1);
	auto r = gameObject()->getComponent<Renderer>();
	auto m = r->material;
	auto shader = m->shader;
	shader->use();
	shader->setFloat("progress", progress);
	shader->setFloat("vanishDis", distance);
}


