#include "UiComponents.h"

namespace ComponentModel
{
	void UiElement::AddChild ( UiElement * child )
	{
		shared_ptr<UiElement> newElement;
		newElement.reset ( child );
		p_children.push_back ( newElement );
		num_children = p_children.size ( );
	}

	///<summary>adds a child UiElement at the index just before the second parameter</summary>

	void UiElement::AddChild ( UiElement * child, int index )
	{
		shared_ptr<UiElement> newElement;
		newElement.reset ( child );
		p_children.insert ( p_children.begin ( ) + index, newElement );
		num_children = p_children.size ( );
	}

	///<summary>seeks this child element and removes it</summary>

	void UiElement::RemoveChild ( UiElement & child )
	{
		for ( int i = 0; i < num_children; ++i )
		{
			if ( p_children[i]->p_id == child.p_id )
			{
				p_children.erase ( p_children.begin ( ) + i );
				break;
			}
		}
	}


	///<summary>removes the last child element added</summary>

	void UiElement::RemoveLastChild ( UiElement & child )
	{
		p_children.pop_back ( );
	}

	void UiElement::Draw ( ) const
	{
		if ( p_visible )
		{
			DrawSelf ( );
			for ( int i = 0; i < num_children; ++i )
			{
				p_children[i]->Draw ( );
			}
		}
	}

	inline void UiElement::Show ( )
	{
		p_visible = true;
	}

	inline void UiElement::InvertVisibility ( )
	{
		p_visible = !p_visible;
	}

	void UiElement::SendToGPU ( ) const
	{
		glBufferData ( GL_ARRAY_BUFFER, sizeof ( p_vertices ), p_vertices, GL_STATIC_DRAW );
	}

	void AbsoluteGeometry::Layout ( )
	{
		if ( p_parent != nullptr )
		{
			p_location.X = p_parent->GetAbsoluteX ( ) + p_relative_geometry.GetX ( );
			p_location.Y = p_parent->GetAbsoluteY ( ) + p_relative_geometry.GetY ( );
		}
		else
		{
			p_location.X = p_relative_geometry.GetX ( );
			p_location.Y = p_relative_geometry.GetY ( );
		}
	}

	int UiElement::id_gen = 0;
}
