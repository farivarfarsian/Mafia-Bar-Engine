#pragma once
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
				Bindable();
				virtual void Bind() = 0;
				virtual ~Bindable() = default;
			protected:
				Graphics* Graphics;
			};
		}
	}
}
