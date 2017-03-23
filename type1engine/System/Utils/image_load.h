#pragma once
#include <iostream>
#include <FreeImage.h>

namespace Engine
{
	namespace Image
	{
		class ImageSrc
		{
		private:
			const char *m_path;
			unsigned int m_width, m_height;
			unsigned int m_bits;
			FIBITMAP  *m_dib;
			BYTE *m_pixels;
		public:
			ImageSrc(const char *p) : m_path(p)
			{
				m_pixels = Init(m_path);
			}
			~ImageSrc()
			{
				FreeImage_Unload(m_dib);
			}

			const unsigned int &GetWidth() const { return m_width; };
			const unsigned int &GetHeight() const { return m_height; };
			BYTE *GetPixels() const { return m_pixels; };
			const unsigned int &GetBits() const { return m_bits; };

			BYTE *Init(const char *path);
		};
	}
}