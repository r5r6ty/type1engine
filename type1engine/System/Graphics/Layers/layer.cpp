#include "layer.h"

namespace Engine
{
	namespace Graphics
	{
		Layer::Layer(Renderer2D *renderer, Shader *shader, glm::mat4 projectmatrix)
			: m_renderer(renderer), m_shader(shader), m_projectmatrix(projectmatrix)
		{
			m_shader->Enable();
			m_shader->SetUniformMat4("pr_matrix", m_projectmatrix);
			m_shader->Disable();
		}

		Layer::~Layer()
		{
			delete m_shader;
			delete m_renderer;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				delete m_renderables[i];
			}
		}

		void Layer::Add(Renderable2D *renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_shader->Enable();
			m_renderer->Begin();
			for (const Renderable2D *renderable : m_renderables)
			{
				m_renderer->Submit(renderable);
			}
			m_renderer->End();
			m_renderer->Flush();
			m_shader->Disable();
		}
	}
}