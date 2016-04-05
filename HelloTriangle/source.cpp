#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "UiRectangle.h"

#define identifier_name( x ) (#x)

using namespace std;

void init ( void );
void display ( void );

void init_shaders ( void );
void init_geometry ( void );

GLuint load_shader ( GLenum shader_type, const char * file_path );
void read_file_contents ( const char * file_path, string & shader_source_code );

unique_ptr<UiRectangle> rect;
Size screen_size ( 512, 512 );

//handles
GLuint shader_program_handle;
GLuint vertex_array_handle;
GLuint vertex_buffer_handle;

int main ( int argc, char ** argv )
{
	glutInit ( &argc, argv );

	glutInitDisplayMode ( GLUT_RGBA );
	glutInitWindowSize ( screen_size.Width, screen_size.Height );
	glutInitContextVersion ( 4, 0 );
	glutInitContextProfile ( GLUT_CORE_PROFILE );
	glutCreateWindow ( "My Window" );
	glewExperimental = GL_TRUE;
	if ( glewInit ( ) )
	{
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit ( EXIT_FAILURE );
	}

	init ( );
	glutDisplayFunc ( display );
	glutMainLoop ( );

	glDeleteVertexArrays ( 1, &vertex_array_handle );
	glDeleteBuffers ( 1, &vertex_buffer_handle );
}

void init ( void )
{
	glViewport ( 0, 0, screen_size.Width, screen_size.Height );

	float r = ( float ) 0u / 255.0f;
	float g = ( float ) 0u / 255.0f;
	float b = ( float ) 128u / 255.0f;

	glClearColor ( r, g, b, 1.0f );

	
	init_geometry ( );
	init_shaders ( );

	//generates the vertex array object
	glGenVertexArrays ( 1, &vertex_array_handle );

	//generates the vertex buffer object
	glGenBuffers ( 1, &vertex_buffer_handle );

	//binds the vertex array
	glBindVertexArray ( vertex_array_handle );

	//binds the vertex buffer
	glBindBuffer ( GL_ARRAY_BUFFER, vertex_buffer_handle );
	rect->SendToGPU ( );

	//link shader and vertex buffer
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof ( GLfloat ), ( GLvoid* ) 0 );
	glEnableVertexAttribArray ( 0 );

	//unbinds vertex array
	glBindVertexArray ( 0 );
}

void display ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT );

	glUseProgram ( shader_program_handle );
	glBindVertexArray ( vertex_array_handle );
	glDrawArrays ( GL_QUADS, 0, 4 );
	glBindVertexArray ( 0 );

	glFlush ( );
}

void init_shaders ( void )
{
	GLuint vertex_shader_handle = load_shader ( GL_VERTEX_SHADER, "VertexShader.glsl" );
	GLuint fragment_shader_handle = load_shader ( GL_FRAGMENT_SHADER, "FragmentShader.glsl" );

	shader_program_handle = glCreateProgram ( );
	glAttachShader ( shader_program_handle, vertex_shader_handle );
	glAttachShader ( shader_program_handle, fragment_shader_handle );
	glLinkProgram ( shader_program_handle );

	GLint success;
	glGetProgramiv ( shader_program_handle, GL_LINK_STATUS, &success );
	GLchar infoLog[512];
	if ( !success )
	{
		glGetProgramInfoLog ( shader_program_handle, 512, NULL, infoLog );
		cout << "[[ERROR]] - Shader Linkage Failed\n" << infoLog << endl;
	}

	glUseProgram ( shader_program_handle );
	glDeleteShader ( vertex_shader_handle );
	glDeleteShader ( fragment_shader_handle );
}

GLuint load_shader ( GLenum shader_type, const char * file_path )
{
	//get handle for shader
	GLuint shader_handle = glCreateShader ( shader_type );

	string source;
	read_file_contents ( file_path, source );

	const char * c_source = source.c_str ( );
	//binds the C string with the source code of the shader to the shader handle
	glShaderSource ( shader_handle, 1, &c_source, NULL );

	//compiles the source code bound to the shader handle
	glCompileShader ( shader_handle );

	//checking for errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv ( shader_handle, GL_COMPILE_STATUS, &success );

	//if there was an error
	if ( !success )
	{
		glGetShaderInfoLog ( shader_handle, 512, NULL, infoLog );
		cout << "[[ERROR]] - Shader Compilation Failed\n(" << file_path << ")\n" << infoLog << endl;
	}

	return shader_handle;
}

void init_geometry ( void )
{
	rect = make_unique<UiRectangle> ( nullptr, 100, 100, 300, 300 );
	rect->GenerateVertices ( screen_size );

	for ( int i = 0; i < 12; ++i )
	{
		cout << "[" << i << "]: " << rect->p_vertices[i] << endl;
	}
}

void read_file_contents ( const char * file_path, string & shader_source_code )
{
	//get handle for file
	ifstream file_reader ( file_path );

	if ( file_reader.is_open ( ) )
	{
		//temporary stringstream
		stringstream buffer;
		//read file to stringstream
		buffer << file_reader.rdbuf ( );
		//get the contents of the stringstream as a C++ string
		shader_source_code = buffer.str ( );
		//clears the stringstream before it goes out of scope
		buffer.clear ( );
		cout << "[[INFO]] - Contents of " << file_path << ":\n" << shader_source_code << "\n" << endl;
	}
	else
	{
		cout << "[[ERROR]] - File Not Found Error\n" << file_path << endl;
	}
	//uses the handle to close the file
	file_reader.close ( );
}
