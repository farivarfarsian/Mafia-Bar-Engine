#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API  Topology : public Bindable
			{
			public:
				Topology(D3D_PRIMITIVE_TOPOLOGY Topolgy);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			private:
				D3D_PRIMITIVE_TOPOLOGY mTopolgyType;
			};
		}
	}
}
