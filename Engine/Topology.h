#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE  Topology : public Bindable
			{
			public:
				Topology(D3D_PRIMITIVE_TOPOLOGY Topolgy);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			public:
			private:
				D3D_PRIMITIVE_TOPOLOGY mTopolgyType;
			};
		}
	}
}
