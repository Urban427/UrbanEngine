#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(const ShaderDesc& desc)
{
	programID = glCreateProgram();
	attach(desc.vertexShaderFilePath, VertexShader);
	attach(desc.fragmentShaderFilePath, FragmentShader);
	link();
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < 2; i++)
	{
		glDetachShader(programID, attachedShaders[i]);
		glDeleteShader(attachedShaders[i]);
	}
	
	glDeleteProgram(programID);
}


void Shader::attach(const char* shaderFilePath, const ShaderType& type)
{
	
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
	
	
	
	
	
	unsigned int shaderID = 0;
	if(type == VertexShader)
	{
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	}
	else
	{
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(shaderID, 1, &buffer, &size);
	glCompileShader(shaderID);
	
	glAttachShader(programID, shaderID);
	attachedShaders[type] = shaderID;
	
	delete[] buffer;
}

void Shader::link()
{
	glLinkProgram(programID);
}

unsigned int Shader::getID()
{
	return programID;
}