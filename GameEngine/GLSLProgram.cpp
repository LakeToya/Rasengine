#include "stdafx.h"
#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>


GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string & VertexShader, const std::string & FragmentShader)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		printf("Error in loading vertexShader");
		return;
	}	
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		printf("Error in loading fragmentShader");
		return;
	}

	CompileShader(VertexShader,_vertexShaderID);
	CompileShader(FragmentShader, _fragmentShaderID);

}

/*
	@brief Link Shaders
*/

void GLSLProgram::LinkShaders()
{
	

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Error Checking below

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		//Use the infoLog as you see fit.
		printf("%s\n", &infoLog[0]);
		printf("Shaders failed to link!!");

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);


}

void GLSLProgram::AddAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}
/*
	@brief Used to ask where the location of the Uniform variable is
*/

GLuint GLSLProgram::GetUnifromLocation(const std::string uniformName)
{
	GLint location =  glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		FatalError("Uniform " + uniformName + " not found in shader..");
	}
	return location;
}

void GLSLProgram::Use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes;i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes;i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::CompileShader(const std::string& filepath, GLuint id)
{
	std::ifstream vertexFile(filepath);
	if (vertexFile.fail())
	{
		printf("Failed to open Shader");
		return;
	}

	std::string fileContent = "";
	std::string line;
	while (std::getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}

	vertexFile.close();

	const char* contentptr = fileContent.c_str();
	glShaderSource(id, 1, &contentptr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		printf("%s\n", &errorLog[0]);
		printf("Shader %s failed to compile", filepath);

		return;
	}

}
