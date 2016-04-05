#pragma once
#include <GL\glew.h>
#include <vector>
#include <cstdint>
#include <memory>
using namespace std;

namespace ComponentModel
{
	enum Direction2D { LEFT, TOP, RIGHT, BOTTOM };
	enum Vertex2D{ BOTTOM_LEFT, TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT };
	enum Coord2D { BOTTOM_LEFT_X, BOTTOM_LEFT_Y, BOTTOM_LEFT_Z, TOP_LEFT_X, TOP_LEFT_Y, TOP_LEFT_Z, TOP_RIGHT_X, TOP_RIGHT_Y, TOP_RIGHT_Z, BOTTOM_RIGHT_X, BOTTOM_RIGHT_Y, BOTTOM_RIGHT_Z };

	struct Location
	{
		GLshort X;
		GLshort Y;

		Location ( GLint x = 0, GLint y = 0 ) :
			X { ( GLshort ) x },
			Y { ( GLshort ) y }
		{

		}
	};

	struct Margin
	{
		GLbyte Left;
		GLbyte Top;
		GLbyte Right;
		GLbyte Bottom;

		Margin ( GLint left = 0, GLint top = 0, GLint right = 0, GLint bottom = 0 ) :
			Left { ( GLbyte ) left }, Top { ( GLbyte ) top }, Right { ( GLbyte ) right }, Bottom { ( GLbyte ) bottom }
		{ }
	};

	struct Size
	{
		GLushort Width;
		GLushort Height;

		Size ( GLuint width, GLuint height ) :
			Width { ( GLushort ) width }, Height { ( GLushort ) height }
		{ }
	};

	enum class ChildrenHint
	{
		///<summary>Child elements can be added, but are unlikely to be removed</summary>
		STATIC,
		///<summary>Child elements can be added, and removed often</summary>
		DYNAMIC
	};

	class RelativeGeometry
	{
		public:

		RelativeGeometry ( GLint relativeX = 0, GLint relativeY = 0, GLint width = 1, GLint height = 1 ) :
			p_location { relativeX, relativeY },
			p_margins { 0 },
			p_size { width, height }
		{ }

		~RelativeGeometry ( )
		{ }

		GLshort inline GetX ( ) const
		{
			return p_location.X;
		}
		GLshort inline GetY ( ) const
		{
			return p_location.Y;
		}
		Location inline GetLocation ( ) const
		{
			return p_location;
		}


		GLbyte inline GetLeftMargin ( ) const
		{
			return p_margins.Left;
		}
		GLbyte inline GetRightMargin ( ) const
		{
			return p_margins.Right;
		}
		GLbyte inline GetTopMargin ( ) const
		{
			return p_margins.Top;
		}
		GLbyte inline GetBottomMargin ( ) const
		{
			return p_margins.Bottom;
		}
		Margin inline GetMargins ( ) const
		{
			return p_margins;
		}


		GLushort inline GetWidth ( ) const
		{
			return p_size.Width;
		}
		GLushort inline GetHeight ( ) const
		{
			return p_size.Height;
		}
		Size inline GetSize ( ) const
		{
			return p_size;
		}


		void inline SetX ( GLint value )
		{
			p_location.X = value;
		}
		void inline SetY ( GLint value )
		{
			p_location.Y = value;
		}
		void inline SetLocation ( Location location )
		{
			p_location = location;
		}


		void inline SetLeftMargin ( GLint value )
		{
			p_margins.Left = value;
		}
		void inline SetRightMargin ( GLint value )
		{
			p_margins.Right = value;
		}
		void inline SetTopMargin ( GLint value )
		{
			p_margins.Top = value;
		}
		void inline SetBottomMargin ( GLint value )
		{
			p_margins.Bottom = value;
		}
		void inline SetMargins ( Margin value )
		{
			p_margins = value;
		}


		void inline SetWidth ( GLuint value )
		{
			p_size.Width = value;
		}
		void inline SetHeight ( GLuint value )
		{
			p_size.Height = value;
		}
		Size inline SetSize ( Size value )
		{
			p_size = value;
		}

		protected:
		Location p_location;
		Margin p_margins;
		Size p_size;
	};

	class UiElement;

	class AbsoluteGeometry
	{
		public:

		explicit AbsoluteGeometry ( UiElement * parent = nullptr, GLint relativeX = 0, GLint relativeY = 0 ) :
			p_parent { parent },
			p_relative_geometry ( relativeX, relativeY )
		{
			Layout ( );
		}

		~AbsoluteGeometry ( )
		{

		}

		GLshort inline GetAbsoluteX ( ) const
		{
			return p_location.X;
		}
		GLshort inline GetAbsoluteY ( ) const
		{
			return p_location.Y;
		}
		Location inline GetAbsoluteLocation ( ) const
		{
			return p_location;
		}


		GLshort inline GetRelativeX ( ) const
		{
			return p_relative_geometry.GetX ( );
		}
		GLshort inline GetRelativeY ( ) const
		{
			return p_relative_geometry.GetY ( );
		}
		Location inline GetRelativeLocation ( ) const
		{
			return p_relative_geometry.GetLocation ( );
		}


		GLbyte inline GetLeftMargin ( ) const
		{
			return p_relative_geometry.GetLeftMargin ( );
		}
		GLbyte inline GetRightMargin ( ) const
		{
			return p_relative_geometry.GetRightMargin ( );
		}
		GLbyte inline GetTopMargin ( ) const
		{
			return p_relative_geometry.GetTopMargin ( );
		}
		GLbyte inline GetBottomMargin ( ) const
		{
			return p_relative_geometry.GetBottomMargin ( );
		}
		Margin inline GetMargins ( ) const
		{
			return p_relative_geometry.GetMargins ( );
		}


		GLushort inline GetWidth ( ) const
		{
			return p_relative_geometry.GetWidth ( );
		}
		GLushort inline GetHeight ( ) const
		{
			return p_relative_geometry.GetHeight ( );
		}
		Size inline GetSize ( ) const
		{
			return p_relative_geometry.GetSize ( );
		}



		void inline SetRelativeX ( GLint value )
		{
			p_relative_geometry.SetX ( value );
		}
		void inline SetRelativeY ( GLint value )
		{
			p_relative_geometry.SetY ( value );
		}
		void inline SetRelativeLocation ( Location value )
		{
			p_relative_geometry.SetLocation ( value );
		}


		void inline SetLeftMargin ( GLint value )
		{
			p_relative_geometry.SetLeftMargin ( value );
		}
		void inline SetRightMargin ( GLint value )
		{
			p_relative_geometry.SetRightMargin ( value );
		}
		void inline SetTopMargin ( GLint value )
		{
			p_relative_geometry.SetTopMargin ( value );
		}
		void inline SetBottomMargin ( GLint value )
		{
			p_relative_geometry.SetBottomMargin ( value );
		}
		void inline SetMargins ( Margin value )
		{
			p_relative_geometry.SetMargins ( value );
		}


		void inline SetWidth ( GLuint value )
		{
			p_relative_geometry.SetWidth ( value );
		}
		void inline SetHeight ( GLuint value )
		{
			p_relative_geometry.SetHeight ( value );
		}
		Size inline SetSize ( Size value )
		{
			p_relative_geometry.SetSize ( value );
		}


		virtual void Layout ( );

		protected:
		RelativeGeometry p_relative_geometry;
		UiElement * p_parent;
		Location p_location;
	};

	class Behaviour
	{
		public:

		Behaviour ( )
		{ }

		~Behaviour ( )
		{ }
	};

	class UiElement
	{
		public:

		UiElement ( const UiElement * const parent, int sizeHint = 0 ) : p_id { id_gen++ }, num_children { 0 }, p_parent { parent }
		{
			p_children.reserve ( sizeHint );
		}

		virtual ~UiElement ( )
		{
			delete[] p_vertices;
		}

		GLshort inline GetAbsoluteX ( ) const
		{
			return p_geometry.GetAbsoluteX ( );
		}
		GLshort inline GetAbsoluteY ( ) const
		{
			return p_geometry.GetAbsoluteY ( );
		}
		Location inline GetAbsoluteLocation ( ) const
		{
			return p_geometry.GetAbsoluteLocation ( );
		}


		GLshort inline GetRelativeX ( ) const
		{
			return p_geometry.GetRelativeX ( );
		}
		GLshort inline GetRelativeY ( ) const
		{
			return p_geometry.GetRelativeY ( );
		}
		Location inline GetRelativeLocation ( ) const
		{
			return p_geometry.GetRelativeLocation ( );
		}


		GLbyte inline GetLeftMargin ( ) const
		{
			return p_geometry.GetLeftMargin ( );
		}
		GLbyte inline GetRightMargin ( ) const
		{
			return p_geometry.GetRightMargin ( );
		}
		GLbyte inline GetTopMargin ( ) const
		{
			return p_geometry.GetTopMargin ( );
		}
		GLbyte inline GetBottomMargin ( ) const
		{
			return p_geometry.GetBottomMargin ( );
		}
		Margin inline GetMargins ( ) const
		{
			return p_geometry.GetMargins ( );
		}


		GLushort inline GetWidth ( ) const
		{
			return p_geometry.GetWidth ( );
		}
		GLushort inline GetHeight ( ) const
		{
			return p_geometry.GetHeight ( );
		}
		Size inline GetSize ( ) const
		{
			return p_geometry.GetSize ( );
		}



		void inline SetRelativeX ( GLint value )
		{
			p_geometry.SetRelativeX ( value );
		}
		void inline SetRelativeY ( GLint value )
		{
			p_geometry.SetRelativeY ( value );
		}
		void inline SetRelativeLocation ( Location value )
		{
			p_geometry.SetRelativeLocation ( value );
		}


		void inline SetLeftMargin ( GLint value )
		{
			p_geometry.SetLeftMargin ( value );
		}
		void inline SetRightMargin ( GLint value )
		{
			p_geometry.SetRightMargin ( value );
		}
		void inline SetTopMargin ( GLint value )
		{
			p_geometry.SetTopMargin ( value );
		}
		void inline SetBottomMargin ( GLint value )
		{
			p_geometry.SetBottomMargin ( value );
		}
		void inline SetMargins ( Margin value )
		{
			p_geometry.SetMargins ( value );
		}


		void inline SetWidth ( GLuint value )
		{
			p_geometry.SetWidth ( value );
		}
		void inline SetHeight ( GLuint value )
		{
			p_geometry.SetHeight ( value );
		}
		Size inline SetSize ( Size value )
		{
			p_geometry.SetSize ( value );
		}

		virtual void Layout ( )
		{
			p_geometry.Layout ( );
		}

		///<summary>adds a child element at the end of the internal list of children</summary>
		void AddChild ( UiElement * child );

		///<summary>adds a child UiElement at the index just before the second parameter</summary>
		void AddChild ( UiElement * child, int index );

		///<summary>seeks this child element and removes it</summary>
		void RemoveChild ( UiElement & child );

		///<summary>removes the last child element added</summary>
		void RemoveLastChild ( UiElement & child );

		void Draw ( ) const;

		bool inline isVisible ( ) const
		{
			return p_visible;
		}

		void inline Show ( );

		void inline Hide ( )
		{
			p_visible = false;
		}

		void inline InvertVisibility ( );
		virtual void SendToGPU ( ) const;
		virtual void GenerateVertices ( Size screenSize ) const = 0;

		mutable GLfloat * p_vertices;

		protected:
		const int p_id;
		bool p_visible;
		
		uint16_t num_vertices;

		Behaviour p_behaviour;
		const UiElement * const p_parent;
		//shared_ptr<UiElement> p_parent;
		AbsoluteGeometry p_geometry;
		vector<shared_ptr<UiElement>> p_children;

		virtual void DrawSelf ( ) const = 0;
		

		private:
		static int id_gen;
		int num_children;
	};
}
