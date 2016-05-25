#pragma once
 
#include "Scene.h"

class MyScene : public Scene
{
private:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_ShaderProgram;
public:
	MyScene();
	virtual ~MyScene();
	void update() override;
};
