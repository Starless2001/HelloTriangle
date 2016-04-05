#include "UiRectangle.h"
#include <iostream>

void UiRectangle::GenerateVertices (Size screenSize ) const
{
	p_vertices = new GLfloat[3 * 4];

	std::cout << "absoluteX: " << p_geometry.GetAbsoluteX ( ) << std::endl;
	std::cout << "absoluteY: " << p_geometry.GetAbsoluteY ( ) << std::endl;
	std::cout << "    width: " << p_geometry.GetWidth ( ) << std::endl;
	std::cout << "   height: " << p_geometry.GetHeight ( ) << std::endl;
	//BOTTOM-LEFT
	p_vertices[BOTTOM_LEFT_X] = (( GLfloat ) p_geometry.GetAbsoluteX ( )) / (( GLfloat ) screenSize.Width);
	p_vertices[BOTTOM_LEFT_Y] = (( GLfloat ) p_geometry.GetAbsoluteY ( )) / (( GLfloat ) screenSize.Height);
	p_vertices[BOTTOM_LEFT_Z] = 0;

	//TOP-LEFT
	p_vertices[TOP_LEFT_X] = (( GLfloat ) p_geometry.GetAbsoluteX ( )) / (( GLfloat ) screenSize.Width);
	p_vertices[TOP_LEFT_Y] = (( GLfloat ) ( p_geometry.GetAbsoluteY ( ) + p_geometry.GetHeight ( ) - 1 )) / (( GLfloat ) screenSize.Height);
	p_vertices[TOP_LEFT_Z] = 0;

	//TOP-RIGHT
	p_vertices[TOP_RIGHT_X] = ( GLfloat ) ( p_geometry.GetAbsoluteX ( ) + p_geometry.GetWidth ( ) - 1 ) / ( GLfloat ) screenSize.Width;
	p_vertices[TOP_RIGHT_Y] = ( GLfloat ) ( p_geometry.GetAbsoluteY ( ) + p_geometry.GetHeight ( ) - 1 ) / ( GLfloat ) screenSize.Height;
	p_vertices[TOP_RIGHT_Z] = 0;

	//BOTTOM-RIGHT
	p_vertices[BOTTOM_RIGHT_X] = ( GLfloat ) ( p_geometry.GetAbsoluteX ( ) + p_geometry.GetWidth ( ) - 1 ) / ( GLfloat ) screenSize.Width;
	p_vertices[BOTTOM_RIGHT_Y] = ( GLfloat ) ( p_geometry.GetAbsoluteY ( ) ) / ( GLfloat ) screenSize.Height;
	p_vertices[BOTTOM_RIGHT_Z] = 0;
}

void UiRectangle::SendToGPU ( ) const
{
	glBufferData ( GL_ARRAY_BUFFER, sizeof ( p_vertices ), p_vertices, GL_STATIC_DRAW );
}
