#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:

	typedef enum
	{
		CAMERA_PERSPECTIVE,
		CAMERA_WHERE,
		CAMERA_FORWARD,
		CAMERA_FOV,
		CAMERA_UP
	} CameraProperty;


	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		Perspective = glm::perspective(fov, aspect, zNear, zFar);
		Where = pos;
		Forward = glm::vec3(0, 0, 1);
		Up = glm::vec3(0, 1, 0);
		this->fov = fov;
	}
	
	inline glm::mat4 GetViewProjection() const
	{
		return Perspective * glm::lookAt(Where, Where + Forward, Up);
	}

	inline void* Get(CameraProperty prop)
	{
		switch (prop)
		{
		case CAMERA_WHERE:
			return &Where;
			break;
		case CAMERA_FORWARD:
			return &Forward;
			break;
		case CAMERA_UP:
			return &Up;
			break;
		case CAMERA_PERSPECTIVE:
			return &Perspective;
			break;
		case CAMERA_FOV:
			return &fov;
			break;
		default: return NULL; break;
		}
	}

private:
	glm::mat4 Perspective;
	glm::vec3 Where;
	glm::vec3 Forward;
	glm::vec3 Up;
	float fov;
};