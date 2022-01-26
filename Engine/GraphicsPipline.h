#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class Pipline
			{
			public:
				void BindThePipline(MafiaBar::Engine::Graphics::Graphics& graphics) { for (auto& b : Binds) { b->Bind(graphics); } }
				void BindToPipline(std::unique_ptr<MafiaBar::Engine::Graphics::Bindable> bind) { Binds.push_back(std::move(bind)); }
			private:
				std::vector<std::unique_ptr<MafiaBar::Engine::Graphics::Bindable>> Binds;
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