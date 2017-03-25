#pragma once
#include "batchrenderer2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Label : public Renderable2D
		{
		public:
			const char *m_Text;
			Fonts::Font *m_font;
		public:
			Label(const char *text, glm::vec2 position, glm::vec2 size, Font *font, unsigned int color);
			void Submit(Renderer2D *renderer) const override;
		};
	}
}