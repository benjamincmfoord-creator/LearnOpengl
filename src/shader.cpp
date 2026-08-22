#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(
        std::ifstream::failbit |
        std::ifstream::badbit
    );

    fShaderFile.exceptions(
        std::ifstream::failbit |
        std::ifstream::badbit
    );

    try
    {
        // Open shader files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // Read files
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close files
        vShaderFile.close();
        fShaderFile.close();

        // Convert streams to strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout
            << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
            << e.what()
            << std::endl;
    }


    // Now compile the shaders
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    checkCompileErrors(vertex, "VERTEX");


    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    checkCompileErrors(fragment, "FRAGMENT");


    // Create shader program
    ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    glLinkProgram(ID);

    checkCompileErrors(ID, "PROGRAM");


    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::use()
{
    glUseProgram(ID);
}


void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(
        glGetUniformLocation(ID, name.c_str()),
        (int)value
    );
}


void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(
        glGetUniformLocation(ID, name.c_str()),
        value
    );
}


void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(
        glGetUniformLocation(ID, name.c_str()),
        value
    );
}


void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(
                shader,
                1024,
                NULL,
                infoLog
            );

            std::cout
                << "ERROR::SHADER_COMPILATION_ERROR of type: "
                << type
                << "\n"
                << infoLog
                << "\n"
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(
                shader,
                1024,
                NULL,
                infoLog
            );

            std::cout
                << "ERROR::PROGRAM_LINKING_ERROR of type: "
                << type
                << "\n"
                << infoLog
                << "\n"
                << std::endl;
        }
    }
}