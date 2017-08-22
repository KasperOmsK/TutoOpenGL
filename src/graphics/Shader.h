#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>

// Classe Shader

class Shader
{
private:
    GLuint m_vertexID;
    GLuint m_fragmentID;
    GLuint m_programID;

    std::string m_vertexSource;
    std::string m_fragmentSource;

public:
    Shader();
    Shader(Shader const &other);
    Shader(std::string vertexSource, std::string fragmentSource);
    ~Shader();

    Shader& operator=(Shader const &shaderACopier);
	//desc : perform all openGL stuff needed to load a shader
	//returns : true if loading succeeded, false otherwise
    bool load();
	
	//desc : tries to compile shader
	//returns : true if compilation suceeded, false otherwise
    bool compileShader(GLuint &shader, GLenum type, std::string const &fichierSource);
    
	//desc : returns the shader ID generated for this shader by OpenGL
	GLuint getProgramID() const;
};
