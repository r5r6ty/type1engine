#pragma once
#include <GL/glew.h>
#include "renderable2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Renderer2D
		{
		public:
			virtual void Begin() = 0;
			virtual void Submit(const Renderable2D *renderable2D) = 0;
			virtual void End() = 0;
			virtual void Flush() = 0;
		};
	}
}