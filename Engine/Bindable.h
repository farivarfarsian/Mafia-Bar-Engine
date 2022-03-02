#pragma once
#include "Exception.h"
#include "Graphics.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Bindable
			{
			public:
				virtual void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) = 0;
				virtual ~Bindable() = default;
			};
		}
	}
}
