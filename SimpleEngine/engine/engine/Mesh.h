#pragma once
#include "Object.h"
namespace yk
{
	class Mesh : public Object
	{
		META_OBJECT
	public:
		STD vector<vec3> vertices;
		STD vector<vec3> normals;
		STD vector<vec3> tangents;
		STD vector<int> triangles;
		STD vector<vec2> uv;
		//void recalculateNormals();
	public:
		void setupMesh()
		{
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			glGenBuffers(1, &m_ebo);

			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			auto s = vertexSize();
			glBufferData(GL_ARRAY_BUFFER, vertexSize(), NULL, GL_STATIC_DRAW);
			if (vertices.size() > 0)
				glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize(), &vertices[0]);
			if (normals.size() > 0)
				glBufferSubData(GL_ARRAY_BUFFER, verticesSize(), normalsSize(), &normals[0]);
			if (tangents.size() > 0)
				glBufferSubData(GL_ARRAY_BUFFER, verticesSize() + normalsSize(), tangentsSize(), &tangents[0]);
			if (uv.size() > 0)
				glBufferSubData(GL_ARRAY_BUFFER, verticesSize() + normalsSize() + tangentsSize(), uvSize(), &uv[0]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			if (triangles.size() > 0)
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, trianglesSize(), &triangles[0], GL_STATIC_DRAW);

			// vertices (location=0)
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
			// normals	(location=1)
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)verticesSize());
			// tangents	(location=2)
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(verticesSize() + normalsSize()));
			// uvs		(location=3)
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(verticesSize() + normalsSize() + tangentsSize()));
			glBindVertexArray(0);
		}
	private:
		friend class MeshRenderer;
		void draw() {
			glBindVertexArray(m_vao);
			glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		size_t verticesSize() { return vertices.size() * sizeof(vec3); }
		size_t normalsSize() { return normals.size() * sizeof(vec3); }
		size_t tangentsSize() { return tangents.size() * sizeof(vec3); }
		size_t uvSize() { return uv.size() * sizeof(vec2); }
		size_t trianglesSize() { return triangles.size() * sizeof(int); }
		size_t vertexSize() { return verticesSize() + normalsSize() + tangentsSize() + uvSize(); }

	private:
		unsigned int m_vao = 0;
		unsigned int m_vbo = 0;
		unsigned int m_ebo = 0;
	};
}