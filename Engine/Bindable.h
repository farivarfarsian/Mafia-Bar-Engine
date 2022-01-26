#pragma once
#include "Engine.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE Bindable
			{
			public:
				virtual void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) = 0;
				virtual ~Bindable() = default;
			};
		}
	}
}
