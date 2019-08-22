#pragma once
#include <GL/glew.h>
#include <vector>
#include "glm/glm.hpp"

class Vertex
{
public:
	Vertex(const glm::vec3& npos, const glm::vec2 ntexCoord)
	{
		this->pos = npos;
		this->texCoord = ntexCoord;
	}
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
private:	
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];
	unsigned int drawCount;

public:
	Mesh(Vertex* vertices, unsigned int numv)
	{
		drawCount = numv;
		
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;

		positions.reserve(numv);
		texCoords.reserve(numv);

		for (unsigned int i = 0; i < numv; i++)
		{
			positions.push_back(vertices[i].pos);
			texCoords.push_back(vertices[i].texCoord);
		}




		
		glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, numv * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			   


		glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, numv * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


		glBindVertexArray(0);
	}

	void Draw()
	{
		glBindVertexArray(vertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, drawCount);

		glBindVertexArray(0);
	}

	~Mesh()
	{
		glDeleteVertexArrays(1, &vertexArrayObject);
	}
};


