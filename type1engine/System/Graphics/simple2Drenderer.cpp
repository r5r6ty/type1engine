#include "simple2Drenderer.h"

namespace Engine
{
	namespace Graphics
	{
		void Simple2DRenderer::Submit(const Renderable2D *renderable2D)
		{
			m_rednerqueue.push_back((StaticSprite*)renderable2D);
		}
		void Simple2DRenderer::Flush()
		{
			while (!m_rednerqueue.empty())
			{
				const StaticSprite *sprite = m_rednerqueue.front();
				sprite->GetVAO()->Bind();
				sprite->GetIBO()->Bind();
				sprite->GetShader()->SetUniformMat4("ml_matrix", glm::translate(glm::mat4(1.0f), sprite->GetPosition()));
				glDrawElements(GL_TRIANGLES, sprite->GetIBO()->GetCount(), GL_UNSIGNED_INT, 0);
				sprite->GetIBO()->UnBind();
				sprite->GetVAO()->UnBind();
				m_rednerqueue.pop_front();
			}

		}
	}
}