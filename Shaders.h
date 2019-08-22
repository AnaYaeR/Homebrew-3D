#pragma once
#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Tranform.h"
#include "Camera.h"

static std::string LoadShader(const std::string fileName);
static GLuint CreateShader(const std::string source, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errMessage);


class Shader
{
private:
	static const unsigned int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};
	
	GLuint Program;
	GLuint Shaders[NUM_SHADER];
	GLuint Uniforms[NUM_UNIFORM];


public:
	Shader(const std::string fName)
	{
		Program = glCreateProgram();
		Shaders[0] = CreateShader(LoadShader(fName + ".vshade"), GL_VERTEX_SHADER);
		Shaders[1] = CreateShader(LoadShader(fName + ".fshade"), GL_FRAGMENT_SHADER);

		for (unsigned int i = 0; i < NUM_SHADER; i++) glAttachShader(Program, Shaders[i]);

		glBindAttribLocation(Program, 0, "position");
		glBindAttribLocation(Program, 1, "texCoord");

		glLinkProgram(Program);
		CheckShaderError(Program, GL_LINK_STATUS, true, "ERROR: Program Link Failure ");

		glValidateProgram(Program);
		CheckShaderError(Program, GL_VALIDATE_STATUS, true, "ERROR: Shader Program Invalid: ");

		Uniforms[TRANSFORM_U] = glGetUniformLocation(Program, "transform");
	}

	void Bind()
	{
		glUseProgram(Program);
	}

	void Update(const eTransform& transform, const Camera& camera)
	{
		glm::mat4 Model = camera.GetViewProjection() * transform.GetModel();


		glUniformMatrix4fv(Uniforms[TRANSFORM_U], 1, GL_FALSE, &Model[0][0]);
	}

	~Shader()
	{
		for (unsigned int i = 0; i < NUM_SHADER; i++)
		{
			glDetachShader(Program, Shaders[i]);
			glDeleteShader(Shaders[i]);
		}

		glDeleteProgram(Program);
	}
};



static std::string LoadShader(const std::string fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		fprintf(stderr, "Unable to load Shader: %s\n", fileName.c_str());
	}

	return output;
}

static GLuint CreateShader(const std::string source, GLenum shaderType)
{
	GLuint Shader = glCreateShader(shaderType);
	if (!Shader) fprintf(stderr, "Error: Shader Creation Failed.");

	const GLchar* shaderSource[1];
	GLint shaderSourceLength[1];

	shaderSource[0] = source.c_str();
	shaderSourceLength[0] = source.length();

	glShaderSource(Shader, 1, shaderSource, shaderSourceLength);
	glCompileShader(Shader);

	CheckShaderError(Shader, GL_COMPILE_STATUS, false, "ERROR: Shader Compilation Failed: ");

	return Shader;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) glGetProgramiv(shader, flag, &success);
	else glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram) glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n", errMessage, error);
	}
	else
	{
		printf("Shader::Success!\n");
	}
}
