#pragma once
#include <string>
#include "batchrenderer2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Label : public Renderable2D
		{
		public:
			// 持有自己的文本拷贝：外部传栈缓冲/临时字符串也安全
			std::string m_Text;
			Fonts::Font *m_font;
		public:
			Label(const char *text, glm::vec2 position, glm::vec2 size, Font *font, unsigned int color);
			void Submit(Renderer2D *renderer) const override;
		};
	}
}