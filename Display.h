#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>

struct DISPLAY
{
	void Update(SDL_Window* window)
	{
		SDL_GL_SwapWindow(window);
	}

	void Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear( GL_COLOR_BUFFER_BIT );
	}
};