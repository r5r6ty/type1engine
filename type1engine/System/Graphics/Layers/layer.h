#pragma once
#include "../renderer2D.h"

namespace Engine
{
	namespace Graphics
	{	
		class Layer
		{
		protected:
			Renderer2D *m_renderer;
			std::vector<Renderable2D*> m_renderables;
			Shader *m_shader;
			glm::mat4 m_projectmatrix;
		protected:
			Layer(Renderer2D *renderer, Shader *shader, glm::mat4 projectmatrix);
		public:
			virtual ~Layer();
			virtual void Add(Renderable2D *renderable);
			virtual void render();
		};
	}
}