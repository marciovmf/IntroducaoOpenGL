#include "MyScene.h"
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include "Util.h"

GLint checkShaderCompilation(GLuint shader)
{
	GLint success = 0;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}

	return success;
}

GLint checkProgramLink(GLuint program)
{
	GLint success = 0;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cerr << "ERROR: PROGRAM LINKING FAILED:" << infoLog << std::endl;
	}

	return success;
}

MyScene::MyScene()
{
	glClearColor(0.5f, 0.5f, 1, 0);
	std::stringstream vertexSourceStream;
	std::stringstream fragmentSourceStream;


	LoadFile("vertex.vs", vertexSourceStream);
	LoadFile("fragment.fs", fragmentSourceStream);
	std::string vertexSource = vertexSourceStream.str();
	std::string fragmentSource = fragmentSourceStream.str();
	const char* buff;

	// Create shader Program
	m_ShaderProgram = glCreateProgram();

	// Vertex shader
	buff = vertexSource.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &buff, NULL);
	glCompileShader(m_VertexShader);
	checkShaderCompilation(m_VertexShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glDeleteShader(m_VertexShader);

	// Fragment shader
	buff = fragmentSource.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &buff, NULL);
	glCompileShader(m_FragmentShader);
	checkShaderCompilation(m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glDeleteShader(m_FragmentShader);

	// Link shader program
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	// Instala o prorama como parte do pipeline de renderizacao.
	glUseProgram(m_ShaderProgram);
}

void MyScene::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

MyScene::~MyScene()
{
	// Libera memoria e deleta os objetos especificados por cada shader

	glDeleteProgram(m_ShaderProgram);
}
