#include "label.h"

namespace Engine
{
	namespace Graphics
	{
		Label::Label(const char *text, glm::vec2 position, glm::vec2 size, Font *font, unsigned int color)
			: m_Text(text), Renderable2D(glm::vec3(position, 0.0f), size, color) ,m_font(font)
		{
		}

		void Label::Submit(Renderer2D *renderer) const
		{
			renderer->DrawString(m_Text, m_postition, *m_font, m_color);
		}
	}
}