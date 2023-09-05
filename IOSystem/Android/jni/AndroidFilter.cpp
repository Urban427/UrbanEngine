#include <jni.h>
#include <malloc.h>
#include "gl2.h"
#include "PNG.h"
#include "AndroidFileManager.h"
#include "VertexArrayObject.h"


GLuint load_png_asset_into_texture(const char* relative_path) {
	
    const RawImageData raw_image_data = readResource(relative_path);
		
		
	GLuint texture_object_id;
    glGenTextures(1, &texture_object_id);
 
    glBindTexture(GL_TEXTURE_2D, texture_object_id);
 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, raw_image_data.width, raw_image_data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raw_image_data.data);
    glGenerateMipmap(GL_TEXTURE_2D);
 
    glBindTexture(GL_TEXTURE_2D, 0);
	
	
    //release_raw_image_data(&raw_image_data);
    //release_asset_data(&png_file);
 
    return texture_object_id;
}


GLuint compile_shader(const GLenum type, const GLchar* source, const GLint length) {
    GLuint shader_object_id = glCreateShader(type);
    GLint compile_status;
 
    glShaderSource(shader_object_id, 1, (const GLchar **)&source, &length);
    glCompileShader(shader_object_id);
    glGetShaderiv(shader_object_id, GL_COMPILE_STATUS, &compile_status);
 
    return shader_object_id;
}

#define BUFFER_OFFSET(i) ((void*)(i))


unsigned int vertexBufferID;
static GLuint texture;
static GLuint program;
static GLuint vertex_shader;
static GLuint fragment_shader;
 
static GLint a_position_location;
static GLint a_texture_coordinates_location;
static GLint u_texture_unit_location;



extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_BACK);
}

void AndroidLogicUpdate()
{
	//VertexBufferData d;
	//VertexArrayObject vbo(d);
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj) 
{
	AndroidFileManager::init(env, &java_obj);
	AndroidLogicUpdate();


	
	
	
	const float rect[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f};
 
 
 
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 12 * 8, rect, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	const File* vertex_shader_source = open("shader.vsh", "rb");
    const File* fragment_shader_source = open("shader.fsh", "rb");
	vertex_shader = compile_shader(GL_VERTEX_SHADER, (const char*)vertex_shader_source->buffer, vertex_shader_source->size);
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, (const char*)fragment_shader_source->buffer, fragment_shader_source->size);
	
	
	program = glCreateProgram();
    GLint link_status;
 
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	
	
	a_position_location = glGetAttribLocation(program, "a_Position");
    a_texture_coordinates_location =  glGetAttribLocation(program, "a_TextureCoordinates");
    u_texture_unit_location = glGetUniformLocation(program, "u_TextureUnit");
	
	
	
	texture = load_png_asset_into_texture("ghost2.b");
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glUseProgram(program);
 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(u_texture_unit_location, 0);
 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(a_position_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));
    glVertexAttribPointer(a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), BUFFER_OFFSET(2 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(a_position_location);
    glEnableVertexAttribArray(a_texture_coordinates_location);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

