#pragma once
#include "UiComponents.h"
using namespace ComponentModel;

class UiRectangle : public UiElement
{
	public:

	UiRectangle ( UiElement * parent, GLint x, GLint y, GLint w, GLint h )
		:UiElement ( parent )
	{
		SetRelativeX ( x );
		SetRelativeY ( y );
		SetWidth ( w );
		SetHeight ( h );
		//p_geometry.SetWidth ( w );
		//p_geometry.SetHeight ( h );
		Layout ( );
	}

	// Inherited via UiElement
	virtual void GenerateVertices ( Size screenSize ) const override;
	virtual void SendToGPU ( ) const override;
};

