#include "Window.h"
#include <iostream>


Window::Window(int width, int height , const char* title)
{
	m_ShouldClose = true;

	// inicializa a biblioca GLFW
	if (!glfwInit())
	{
		std::cerr << "Erro inicializando GLFW" << std::endl;
		return;
	}

	// Definicao dos atributos do contexto OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	glfwSetErrorCallback(Window::errorCallback);

	// Criar a janela
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_Window)
	{
		std::cerr << "Erro criando janela" << std::endl;
		return;
	}

	// Torna o contexto atual
	glfwMakeContextCurrent(m_Window);

	GLenum glewInitErr = glewInit();

	if (glewInitErr != GLEW_OK)
	{
		std::cerr << "Erro inicializando GLEW: " << glewGetErrorString(glewInitErr) << std::endl;
		return;
	}

	// Mostra dados do ambiente
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderizador: " << renderer << std::endl;
	std::cout << "Versao do opengl suportada: " << version << std::endl;

	glClearColor(0.5f, 0.5f, 1, 0 );

	m_ShouldClose = false;
}

void Window::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();
	glfwSwapBuffers(m_Window);

	if (!m_ShouldClose)
		m_ShouldClose = glfwWindowShouldClose(m_Window);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::errorCallback(int error, const char* description)
{
	std::cerr << "Erro " << error << ": " << description << std::endl;
}