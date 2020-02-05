#pragma once
#include <ykEngine.h>
using namespace std;

namespace yk
{
	class CamMoveCtrl : public MonoBehaviour
	{
		META_OBJECT
	public:
		float factor = 0.05f;
		bool cursorEnable = false;
		void moving(string dir)
		{
			cout << "moving" << dir << "--";
		}

		void Awake() override
		{
			//glfwSetInputMode(&(*RenderMgr::window()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			//RenderMgr::window()->SetCursorEnable(false);
		}

		void Update() override
		{
			if (Input::getkey(GLFW_KEY_A) || Input::getkeydown(GLFW_KEY_A))
			{
				auto delta = 0.1f * transform()->right();
				transform()->position() -= 0.1f * transform()->right();
				moving("left");
				cout << transform()->position() << endl;
			}

			if (Input::getkey(GLFW_KEY_D) || Input::getkeydown(GLFW_KEY_D))
			{
				auto delta = 0.1f * transform()->right();
				transform()->position() += delta;
				moving("right");
				cout << transform()->position() << endl;

			}

			if (Input::getkey(GLFW_KEY_W) || Input::getkeydown(GLFW_KEY_W))
			{
				transform()->position() += 0.1f * transform()->forward();
				moving("up");
				cout << transform()->position() << endl;

			}

			if (Input::getkey(GLFW_KEY_S) || Input::getkeydown(GLFW_KEY_S))
			{
				transform()->position() -= 0.1f * transform()->forward();
				moving("down");
				cout << transform()->position() << endl;

			}

			if (Input::getkey(GLFW_KEY_Q) || Input::getkeydown(GLFW_KEY_Q))
			{
				transform()->position() -= 0.1f * transform()->up();
			}

			if (Input::getkey(GLFW_KEY_E) || Input::getkeydown(GLFW_KEY_E))
			{
				transform()->position() += 0.1f * transform()->up();
			}

			if (Input::getkey(GLFW_MOUSE_BUTTON_2))
			{
				float angleX = Input::getCursorDeltaX();
				float angleY = Input::getCursorDeltaY();

				if (angleX != 0)
				{
					auto rotX = angleX * factor;
					transform()->rotate(rotX, vec3(0, 1, 0));
				}

				if (angleY != 0)
				{
					auto rotY = angleY * factor;
					transform()->rotate(rotY, transform()->right());
				}
			}

			if (Input::getkey(GLFW_KEY_LEFT))
			{
				transform()->rotate(0.5f, transform()->up());
			}


			if (Input::getkey(GLFW_KEY_RIGHT))
			{
				transform()->rotate(-0.5f, transform()->up());
			}

			if (Input::getkeydown(GLFW_KEY_UP))
			{
				factor += 0.1f;
			}

			if (Input::getkeydown(GLFW_KEY_DOWN))
			{
				factor -= 0.1f;
			}

			if (Input::getkeydown(GLFW_KEY_SPACE))
			{
				transform()->debug();
				cout << "factor: " << factor << endl;
			}

			//if (Input::getkeydown(GLFW_MOUSE_BUTTON_2))
			//{
			//	RenderMgr::window()->SetCursorEnable(false);
			//}

			//if (Input::getkeyup(GLFW_MOUSE_BUTTON_2))
			//{
			//	//cout << "mouse released!" << endl;
			//	RenderMgr::window()->SetCursorEnable(true);
			//}

			if (Input::getkeydown(GLFW_KEY_ENTER))
			{
				cursorEnable = !cursorEnable;
				RenderMgr::window()->SetCursorEnable(cursorEnable);
			}
		}
	};
}