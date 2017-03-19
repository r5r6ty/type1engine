#include "label.h"

namespace Engine
{
	namespace Graphics
	{
		Label::Label(const char *text, glm::vec2 position, glm::vec2 size, glm::vec4 color)
			: m_Text(text), Renderable2D(glm::vec3(position, 0.0f), size, color)
		{
			//ChangeText(Renderer2D *renderer);
		}

		void Label::Submit(Renderer2D *renderer) const
		{
			renderer->ChangeText(m_Text);
			renderer->DrawString(m_Text, m_postition, m_color);
		}
	}
}