#include "image_load.h"

namespace Engine
{
	namespace Image
	{
		BYTE *ImageSrc::Init(const char *path)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			fif = FreeImage_GetFileType(path, 0);
			FIBITMAP  *dib = nullptr;
			if (fif == FIF_UNKNOWN)
			{
				printf("Could not open: %s\n", path);
				fif = FreeImage_GetFIFFromFilename(path);
			}
			else
			{
				printf("Opened: %s\n", path);
			}
			if (fif == FIF_UNKNOWN)
			{
				return nullptr;
			}
			if (FreeImage_FIFSupportsReading(fif))
			{
				dib = FreeImage_Load(fif, path);
			}
			if (!dib)
			{
				return nullptr;
			}
			else
			{
				m_dib = dib;
				BYTE *pixels = FreeImage_GetBits(dib);
				m_width = FreeImage_GetWidth(dib);
				m_height = FreeImage_GetHeight(dib);
				m_bits = FreeImage_GetBPP(dib);

				return pixels;
			}
		}
	}
}