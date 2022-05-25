#include "pch.h"
#include "Shader.h"
#include "imgui.h"

#include <glad/glad.h>

namespace Ember {

    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);
        // check for shader compile errors
        GLint success = 0;
        std::vector<GLchar> infoLog(512);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            
            glGetShaderInfoLog(vertexShader, 512, NULL, &infoLog[0]);

            glDeleteShader(vertexShader);

            EMBER_CORE_ERR("Vertex shader: {0}", infoLog.data());
            EMBER_CORE_ASSERT(false, "Vertex shader compilation failure!");
        }

        // fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            
            glGetShaderInfoLog(fragmentShader, 512, NULL, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            EMBER_CORE_ERR("Fragment shader: {0}", infoLog.data());
            EMBER_CORE_ASSERT(false, "Fragment shader compilation failure!");
        }

        // -------------link shader--------------
        // link shaders
        rendererID = glCreateProgram();
        glAttachShader(rendererID, vertexShader);
        glAttachShader(rendererID, fragmentShader);
        glLinkProgram(rendererID);

        // check for linking errors
        glGetProgramiv(rendererID, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            
            glGetProgramInfoLog(rendererID, 512, NULL, &infoLog[0]);

            glDeleteProgram(rendererID);
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            EMBER_CORE_ERR("Shader link: {0}", infoLog.data());
            EMBER_CORE_ASSERT(false, "Shader link failure!");
        }

        // 构建完shader程序后，就不需要源文件了
        // 分离代码
        glDetachShader(rendererID, vertexShader);
        glDetachShader(rendererID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(rendererID);
    }

    void Shader::bind() const {
        glUseProgram(rendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }
}