#pragma once
#include <deque>
#include <glm/gtc/matrix_transform.hpp>
#include "renderer2D.h"
#include "static_sprite.h"

namespace Engine
{
	namespace Graphics
	{
		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_rednerqueue;
		public:
			void Submit(const Renderable2D *renderable2D) override;
			void Flush() override;
		};
	}
}