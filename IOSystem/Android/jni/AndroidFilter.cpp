#include <jni.h>
#include <malloc.h>
#include "gl2.h"
#include "PNG.h"
#include "AndroidFileManager.h"
 
GLuint create_vbo(const GLsizeiptr size, const GLvoid* data, const GLenum usage) {
    GLuint vbo_object;
    glGenBuffers(1, &vbo_object);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_object);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
    return vbo_object;
}

GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length) {
    GLuint shader_object_id = glCreateShader(type);
    GLint compile_status;
 
    glShaderSource(shader_object_id, 1, (const GLchar **)&source, &length);
    glCompileShader(shader_object_id);
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);
    return shader_object_id;
}

GLuint link_program(const GLuint vertex_shader, const GLuint fragment_shader) {
    GLuint program_object_id = glCreateProgram();
    GLint link_status;
 
    glAttachShader(program_object_id, vertex_shader);
    glAttachShader(program_object_id, fragment_shader);
    glLinkProgram(program_object_id);
    glGetProgramiv(program_object_id, GL_LINK_STATUS, &link_status);
 
    return program_object_id;
}

GLuint build_program(
    const GLchar * vertex_shader_source, const GLint vertex_shader_source_length, 
    const GLchar * fragment_shader_source, const GLint fragment_shader_source_length) {
 
    GLuint vertex_shader = compile_shader(
        GL_VERTEX_SHADER, vertex_shader_source, vertex_shader_source_length);
    GLuint fragment_shader = compile_shader(
        GL_FRAGMENT_SHADER, fragment_shader_source, fragment_shader_source_length);
    return link_program(vertex_shader, fragment_shader);
}
 
GLuint load_texture(
    const GLsizei width, const GLsizei height,
    const GLenum type, const GLvoid* pixels) 
{
    GLuint texture_object_id;
    glGenTextures(1, &texture_object_id);
 
    glBindTexture(GL_TEXTURE_2D, texture_object_id);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
 
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture_object_id;
}






extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	AndroidFileManager::init(env, &java_obj);
	
	RawImageData img = readBMPFile("ghost2.bmp");
	
}

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj) 
{
	AndroidFileManager::init(env, &java_obj);
	
	
	print("lol");
	
	glClear(GL_COLOR_BUFFER_BIT);
	
}
