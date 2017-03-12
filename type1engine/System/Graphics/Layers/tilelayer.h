#pragma once
#include "layer.h"

namespace Engine
{
	namespace Graphics
	{
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader *shader);
			~TileLayer();
		};
	}
}