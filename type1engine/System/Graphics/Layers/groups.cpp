#include "groups.h"

namespace Engine
{
	namespace Graphics
	{
		Group::Group(const glm::mat4 &transform)
			: m_transformationmatrix(transform)
		{

		}

		void Group::Add(Renderable2D *renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Group::Submit(Renderer2D *renderer) const
		{
			renderer->Push(m_transformationmatrix);
			for (const Renderable2D *renderable : m_renderables)
			{
				renderable->Submit(renderer);
			}
			renderer->Pop();
		}
	}
}