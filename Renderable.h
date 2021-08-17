#ifndef RENDERABLE
#define RENDERABLE

#include <cstdint>
#include <string>
#include <vector>
#include <gl/glew.h>

class Renderable
{
private:

	std::vector<GLfloat> vertices;
	GLuint VAO, VBO, shader;
	std::string vShaderCode, fShaderCode;

public:

	Renderable(const std::vector<GLfloat>& vertices, std::string vShaderCode, std::string fShaderCode);
	Renderable(GLfloat* vertices, size_t size, std::string vShaderCode, std::string fShaderCode);
	~Renderable();

	bool AddShader(GLuint program, std::string shaderCode, GLenum shaderType);
	void Create();
	void Render();
	bool CompileShaders();
};

#endif



