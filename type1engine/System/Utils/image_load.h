#pragma once
#include <FreeImage.h>

namespace Engine
{
	static BYTE *LoadImage(const char *path, GLsizei *width, GLsizei *hegith)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		fif = FreeImage_GetFileType(path, 0);
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(path);
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
		BYTE *result = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*hegith = FreeImage_GetHeight(dib);
		return result;
	}
}