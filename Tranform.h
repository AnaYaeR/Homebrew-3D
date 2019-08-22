#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class eTransform
{
public:

	eTransform(const glm::vec3& npos, const glm::vec3& nrot, const glm::vec3& nscale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		pos = npos;
		rot = nrot;
		scale = nscale;
	}

	glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(pos);
		glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::translate(scale);

		// Matrix Multipications: Not Commutative!!!

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};