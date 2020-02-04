#pragma once
#include <set>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <type_traits>
#include <chrono>
#include <functional>
#include "MetaObject.h"
#include <algorithm>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace yk
{
	class Object : public STD enable_shared_from_this<Object>
	{
		META_OBJECT
	public:
		Object();
		STD string name = "";
		int getInstanceID();
		virtual STD string toString();
		void setParent(STD shared_ptr<Object> parent);
		STD vector<STD shared_ptr<Object>> children();
		STD shared_ptr<Object> findChild(STD string&& name);
		STD shared_ptr<Object> findChild(STD string& name);
		operator bool() const;

	private:
		bool m_alive = true;
		int m_instanceID = -1;
		STD weak_ptr<Object> m_parent;
		STD vector<STD shared_ptr<Object>> m_children;
	};
}