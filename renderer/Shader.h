#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader {
public:
    Shader() = default;
    ~Shader();

    bool load(const std::string& vertexPath, const std::string& fragPath);

    void use() const;

    // Uniform helpers
    void setBool (const std::string& name, bool value)  const;
    void setInt  (const std::string& name, int value)   const;
    void setFloat(const std::string& name, float value) const;

    void setVec2(const std::string& name, const glm::vec2& v) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
    void setVec4(const std::string& name, const glm::vec4& v) const;

    void setMat4(const std::string& name, const glm::mat4& m) const;

private:
    GLuint programID = 0;
    std::string loadFile(const std::string& path) const;
    GLuint compileShader(GLenum type, const std::string& source) const;


};