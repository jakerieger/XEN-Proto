// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Shader.h"

#include <glad/glad.h>

Shader::Shader(const str& vertexCode, const str& fragmentCode) {
    CompileShaders(vertexCode, fragmentCode);
}

Shader::~Shader() {
    glDeleteProgram(mProgram);
}

void Shader::Bind() const {
    glUseProgram(mProgram);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::CompileShaders(const str& vertexCode, const str& fragmentCode) {
    const auto vCode = vertexCode.c_str();
    const auto fCode = fragmentCode.c_str();

    const u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vCode, None);
    glCompileShader(vertexShader);

    const u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fCode, None);
    glCompileShader(fragmentShader);

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);
    glValidateProgram(mProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetBool(const str& name, bool value) const {
    glUniform1i(glGetUniformLocation(mProgram, name.c_str()), CAST<i32>(value));
}

void Shader::SetInt(const str& name, i32 value) const {
    glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::SetFloat(const str& name, f32 value) const {
    glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::SetVec2(const str& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const str& name, f32 x, f32 y) const {
    glUniform2f(glGetUniformLocation(mProgram, name.c_str()), x, y);
}

void Shader::SetVec3(const str& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const str& name, f32 x, f32 y, f32 z) const {
    glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
}

void Shader::SetVec4(const str& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const str& name, f32 x, f32 y, f32 z, f32 w) const {
    glUniform4f(glGetUniformLocation(mProgram, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const str& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const str& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const str& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}