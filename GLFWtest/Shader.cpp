#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile,fragmentFile;
	string vertexString, fragmentString;
	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		if (!vertexFile.is_open()||!fragmentFile.is_open())
		{
			throw std::exception("file open error");
		}
			stringstream vertexSStream, fragmentSStream;
			vertexSStream << vertexFile.rdbuf();
			fragmentSStream << fragmentFile.rdbuf();
			vertexString = vertexSStream.str();
			fragmentString = fragmentSStream.str();
			vertexSource = vertexString.c_str();
			fragmentSource = fragmentString.c_str();

			//printf(vertexSource);
			//printf(fragmentSource);
			unsigned int vertex, fragment;
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vertexSource, NULL);
			glCompileShader(vertex);
			checkCompileError(vertex, "VERTEX");

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fragmentSource, NULL);
			glCompileShader(fragment);
			checkCompileError(fragment, "FRAGMENT");

			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			checkCompileError(ID, "PROGRAM");

			glDeleteShader(vertex);
			glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileError(unsigned int id, const char* type)
{
	int success;
	char infoLog[512];
	if (type!="PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			cout << "shader compile error:" << infoLog << endl;
		}
		else
		{
			cout << type << "->shader compile successed" << endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			cout << "program linking error:" << infoLog << endl;
		}
		else
		{
			cout << type << "->program linking successed" << endl;
		}
	}
}

// utility uniform functions
	// ------------------------------------------------------------------------
void Shader::setBool(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const char* name, int value) 
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const char* name, float x, float y)
{
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const char* name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}