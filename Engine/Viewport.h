#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Viewport : public Bindable
			{
			public:
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics);
				Viewport(MafiaBar::Engine::Graphics::Graphics& graphics, float Width, float Height);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			public:
				D3D11_VIEWPORT GetViewport() const;
			private:
				D3D11_VIEWPORT mViewport;
			};
		}
	}
}
