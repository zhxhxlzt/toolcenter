#pragma once
#include <set>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <chrono>
#include <functional>
#include "MetaObject.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace glm;
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

inline STD ostream& operator<< (STD ostream& s, glm::vec3 v)
{
	s << v.x << ", " << v.y << "," << v.z;
	return s;
}

inline STD ostream& operator<< (STD ostream& s, glm::vec4 v)
{
	s << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
	return s;
}

inline STD ostream& operator<< (STD ostream& s, glm::quat v)
{
	s << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
	return s;
}

inline STD ostream& operator<< (STD ostream& s, glm::mat4 m)
{
	s << "[[" << m[0] << "][" << m[1] << "][" << m[2] << "][" << m[3] << "]]" << endl;
	return s;
}