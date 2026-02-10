#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::~Shader()
{
    if (programID != 0)
        glDeleteProgram(programID);
}

bool Shader::load(const std::string& vertexPath,
                  const std::string& fragmentPath)
{
    std::string vertSrc = loadFile(vertexPath);
    std::string fragSrc = loadFile(fragmentPath);

    if (vertSrc.empty() || fragSrc.empty())
        return false;

    GLuint vertShader = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragShader = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    if (!vertShader || !fragShader)
        return false;

    programID = glCreateProgram();
    glAttachShader(programID, vertShader);
    glAttachShader(programID, fragShader);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "Shader link error:\n" << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return true;
}

void Shader::use() const
{
    glUseProgram(programID);
}
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& v) const
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &v[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& v) const
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &v[0]);
}

void Shader::setVec4(const std::string& name, const glm::vec4& v) const
{
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &v[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& m) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(programID, name.c_str()),
        1,
        GL_FALSE,
        &m[0][0]
    );
}
std::string Shader::loadFile(const std::string& path) const
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return {};
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source) const
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}
