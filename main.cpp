#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#pragma warning(disable:4996)

#include "def.h"
#include "vertex_buffer.h"
#include "Shader.h"

void oldtriangle();


int main()
{

	SDL_Window* window;

	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_WINDOW_OPENGL;


	window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, flags);


	SDL_GLContext glContext = SDL_GL_CreateContext(window);



	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Fehler: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return 1;
	}

	Uint32 numVert_tr2 = 3;

	Vertex tr2[] =
	{
		Vertex{-1.0f, 1.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{-1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 1.0f},
		Vertex{0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 1.0f}
	};

	Uint32 numVert_rect = 4;

	Vertex rect[] =
	{
		Vertex{-0.5f, 0.5f, 0.0f,
				0.0f, 1.0f, 0.0f, 1.0f},
		Vertex{0.5f, 0.5f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f},
		Vertex{-0.5f, -0.5f, 0.0f,
				0.0f, 0.0f, 1.0f, 1.0f},
		Vertex{0.5f, -0.5f, 0.0f,
				0.0f, 1.0f, 0.0f, 1.0f }
	};



	VertexBuffer vertexBuffer2(tr2, numVert_tr2);
	vertexBuffer2.unbind();

	VertexBuffer vertexBufferRect(rect, numVert_rect);
	vertexBufferRect.unbind();


	Sh shader("vertex.vs", "fragment.fs");
	shader.bind();


	uint64_t perCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastCounter = SDL_GetPerformanceCounter();
	float deltaT = 0.0f;


	bool close = false;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	while (!close)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		vertexBuffer2.bind();
		glDrawArrays(GL_TRIANGLES, 0, numVert_tr2);
		vertexBuffer2.unbind();

		vertexBufferRect.bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, numVert_rect);
		vertexBufferRect.unbind();


		SDL_GL_SwapWindow(window);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				close = true;
			}
		}

		uint64_t endCounter = SDL_GetPerformanceCounter();
		uint64_t counterEllapsed = endCounter - lastCounter;
		deltaT = ((float)counterEllapsed) / (float)perCounterFrequency;
		uint32_t fps = (uint32_t)((float)perCounterFrequency) / (float)counterEllapsed;
		std::cout << fps << std::endl;
		lastCounter = endCounter;
	}
	return 0;
}
