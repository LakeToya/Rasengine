#pragma once
#include <string>
#include <GL/glew.h>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();


	void CompileShaders(const std::string &VertexShader, 
		const std::string &FragmentShader);
	void LinkShaders();
	void AddAttribute(const std::string& attributeName);
	GLuint GetUnifromLocation(const std::string uniformName);
	void Use();
	void Unuse();

private:
	int _numAttributes;
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void CompileShader(const std::string& filepath, GLuint id);
};

