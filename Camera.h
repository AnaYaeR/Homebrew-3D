#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		Perspective = glm::perspective(fov, aspect, zNear, zFar);
		Where = pos;
		Forward = glm::vec3(0, 0, 1);
		Up = glm::vec3(0, 1, 0);
	}
	
	inline glm::mat4 GetViewProjection() const
	{
		return Perspective * glm::lookAt(Where, Where + Forward, Up);
	}

private:
	glm::mat4 Perspective;
	glm::vec3 Where;
	glm::vec3 Forward;
	glm::vec3 Up;
};