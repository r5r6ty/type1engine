#pragma once
#include "../renderable2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D *> m_renderables;
		public:
			glm::mat4 m_transformationmatrix;
		public:
			Group(const glm::mat4 &transform);
			~Group();
			void Add(Renderable2D *renderable);
			void Submit(Renderer2D *renderer) const override;
		};
	}
}