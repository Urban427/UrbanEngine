#include "Shader.h"

#ifdef glad
	#include <stdio.h>
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif

Shader::Shader(const ShaderDesc& desc)
{
	programID = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

void Shader::init(const ShaderDesc& desc)
{
	programID = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

Shader::~Shader()
{
	#ifdef glad
	for(unsigned int i = 0; i < 2; i++)
	{
		glDetachShader(programID, attachedShaders[i]);
		glDeleteShader(attachedShaders[i]);
	}
	
	glDeleteProgram(programID);
	#endif
}


void Shader::attach(const char* shaderFilePath, const ShaderType& type)
{
	/*
	char* buffer;
	int size;
	FILE* f = fopen(shaderFilePath, "rb");
	if(!f) {
		return;
	}
	
	fseek(f, 0, SEEK_END);
    size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	buffer = new char[size];
	fread(buffer, size, sizeof(char), f);
	fclose(f);
	*/
	
	
	
	
	unsigned int shaderID = 0;
	if(type == VertexShader)
	{
		const char* buffer = 
		"attribute vec4 a_Position;"
		"attribute vec2 a_TextureCoordinates;"
		"varying vec2 v_TextureCoordinates;"
		
		"uniform mat4 transform;"
		"uniform mat4 projection;"
		"void main(){"
		"	gl_Position =  transform * a_Position;"
		"	v_TextureCoordinates = a_TextureCoordinates.xy;"
		"}";
		
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shaderID, 1, &buffer, NULL);
	}
	else
	{
		const char* buffer = 
		"precision mediump float;"
		"varying vec2 v_TextureCoordinates;"
		
		"uniform sampler2D u_TextureUnit;"
		"void main(){"
		"	gl_FragColor = texture2D(u_TextureUnit, v_TextureCoordinates.xy);"
		"	gl_FragColor = vec4(0, 0, 0, 1);"
		"}";
		
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shaderID, 1, &buffer, NULL);
	}

	//glShaderSource(shaderID, 1, &buffer, &size);
	glCompileShader(shaderID);
	
	glAttachShader(programID, shaderID);
	attachedShaders[type] = shaderID;
	
	//delete[] buffer;
}

void Shader::link()
{
	glLinkProgram(programID);
}

unsigned int Shader::getID()
{
	return programID;
}