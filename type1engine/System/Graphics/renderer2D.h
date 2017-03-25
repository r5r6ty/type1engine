#pragma once
#include <vector>
#include <GL/glew.h>
#include "../Fonts/font.h"

namespace Engine
{
	namespace Graphics
	{
		class Renderable2D;

		using namespace Fonts;

		class Renderer2D
		{
		protected:
			std::vector<glm::mat4> m_transformationstack;
			const glm::mat4 *m_m_transformationback;
		protected:
			Renderer2D()
			{
				m_transformationstack.push_back(glm::mat4(1.0f));
				m_m_transformationback = &m_transformationstack.back();
			}
		public:
			void Push(glm::mat4 matrix, bool override = false)
			{
				if (override)
				{
					m_transformationstack.push_back(matrix);
				}
				else
				{
					m_transformationstack.push_back(m_transformationstack.back() * matrix);
				}
				m_m_transformationback = &m_transformationstack.back();
			}

			void Pop()
			{
				if(m_transformationstack.size() > 1)
				{
					m_transformationstack.pop_back();
				}
				m_m_transformationback = &m_transformationstack.back();
			}

			virtual void Begin() {}
			virtual void Submit(const Renderable2D *renderable2D) = 0;
			virtual void DrawString(const char *text, const glm::vec3 &position, Font &font, unsigned int color) {}
			virtual void End() {}
			virtual void Flush() = 0;
		};
	}
}