#include "Renderable.h"

#include <iostream>

Renderable::Renderable(const std::vector<GLfloat>& vertices, 
					   std::string vShaderCode, 
					   std::string fShaderCode)
	: vertices(vertices), vShaderCode(vShaderCode), fShaderCode(fShaderCode),
	  VAO(0), VBO(0), shader(0)
{
	//Create();
	//CompileShaders(vShaderCode, fShaderCode);
}

Renderable::Renderable(GLfloat* vertices, size_t size, 
					   std::string vShaderCode, 
					   std::string fShaderCode)
	: vShaderCode(vShaderCode), fShaderCode(fShaderCode),
	  VAO(0), VBO(0), shader(0)
{
	this->vertices = std::vector<GLfloat>(vertices[0], size);
}

Renderable::~Renderable()
{
	glDeleteProgram(shader);
}

void Renderable::Create()
{
	if (!this->vertices.empty())
	{
		std::cout << "Num Vertices: " << vertices.size() << '\n';
		size_t size = vertices.size();
		GLfloat* vertexArr = new GLfloat[size];
		for (int i = 0; i < size; i++)
		{
			//std::cout << i << '\n';
			vertexArr[i] = vertices[i];
		}

		for (int i = 0; i < size; i++)
		{
			std::cout << "Vertex: " << vertexArr[i] << '\n';
		}

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertexArr[0]), vertexArr, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	else
	{
		std::cout << "Vertices is Empty\n";
	}

	if (CompileShaders()) std::cout << "Compiled shaders successfully!\n";
}

void Renderable::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glUseProgram(0);
}

bool Renderable::AddShader(GLuint program, std::string shaderCode, GLenum shaderType)
{
	std::cout << "Adding " << shaderType << " to the code\n";
	std::cout << "\n\n" << shaderCode << "\n\n";
	GLint shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode.c_str();

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode.c_str());

	glShaderSource(shader, 1, code, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << " program: " << eLog << '\n';
		return false;
	}

	glAttachShader(program, shader);

	return true;
}

bool Renderable::CompileShaders()
{
	shader = glCreateProgram();

	if (!shader) std::cout << "Error Creating Shader\n";

	if (!AddShader(shader, vShaderCode.c_str(), GL_VERTEX_SHADER) ||
		!AddShader(shader, fShaderCode.c_str(), GL_FRAGMENT_SHADER))
		return false;

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: " << eLog << '\n';
		return false;
	}

	glValidateProgram(shader);

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: " << eLog << '\n';
		return false;
	}

	return true;
}
