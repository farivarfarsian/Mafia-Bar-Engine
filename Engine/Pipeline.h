#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class __declspec(dllexport) Pipeline final
			{

			public:
				Pipeline() = default;
				~Pipeline();
				Pipeline(Pipeline& Pipeline) = delete;
				Pipeline& operator=(const Pipeline&) = delete;
				void BindThePipline(Graphics& Graphics);
				void AddBindable(Bindable* Bind);
				static constexpr bool IsStaticBindablesInitialized();
				static void AddStaticBindable(Bindable* Bind);
				static void BindTheStaticPipline(Graphics& Graphics);
			private:
				MafiaBar::SDK::Vector<Bindable*> Bindables;
				static MafiaBar::SDK::Vector<Bindable*> StaticBindables;
			};
		}
	}
}


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "InputLayout.h"
#include "Topology.h"
#include "Viewport.h"
#include "TransformCbuf.h"