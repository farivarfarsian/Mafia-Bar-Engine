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
				~Pipeline() = default;
				Pipeline(Pipeline& Pipeline) = delete;
				Pipeline& operator=(const Pipeline&) = delete;
				void BindThePipline();
				void AddBindable(const std::shared_ptr<Bindable>& Bind);
				void AddBindable(std::shared_ptr<Bindable>&& Bind);
				static constexpr bool IsStaticBindablesInitialized();
				static void AddStaticBindable(const std::shared_ptr<Bindable>& Bind);
				static void AddStaticBindable(std::shared_ptr<Bindable>&& Bind);
				static void BindTheStaticPipline();
			private:
				MafiaBar::SDK::Vector<std::shared_ptr<Bindable>> Bindables;
				static MafiaBar::SDK::Vector<std::shared_ptr<Bindable>> StaticBindables;
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