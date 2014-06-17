#pragma once

#include "Singleton.h"

#include "common.h"

using namespace std;

enum ShaderType_t
{

	VERTEX,
	FRAGMENT,
	LAST

};

class ShaderManager : public Singleton<ShaderManager>
{

	friend class Singleton<ShaderManager>;

public:

	ShaderManager();
	~ShaderManager();

	GLuint loadShader(ShaderType_t shaderType, string path);
	GLuint loadShaderSet(string vertexShaderPath, string fragmentShaderPath);

};