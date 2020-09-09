#pragma once

#include <glm/glm.hpp>
#include <string>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	const char* vertexSource;
	const char* fragmentSource;
	void use();
	unsigned int ID;
	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVec2(const char* name, float x, float y);
	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec3(const char* name, float x, float y, float z);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec4(const char* name, float x, float y, float z, float w);
	void setMat4(const std::string& name, const glm::mat4& mat);

private:
	void checkCompileError(unsigned int id, const char* type);
};

