#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			template <class ConstantTemplateType>
			class EXP_ENGINE ConstantBuffer : public Bindable
			{
			public:
				ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType);
				ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics);
				void Update(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType);
			protected:
				Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
			};

			template <class VertexConstantTemplateType>
			class EXP_ENGINE VertexConstantBuffer : public ConstantBuffer<VertexConstantTemplateType>
			{
				using ConstantBuffer<VertexConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<VertexConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			};

			template <class PixelConstantTemplateType>
			class EXP_ENGINE PixelConstantBuffer : public ConstantBuffer<PixelConstantTemplateType>
			{
				using ConstantBuffer<PixelConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<PixelConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			};
		}
	}
}
