#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE IndexBuffer : public Bindable
			{
				//Please Replace The STD::vector with MafiaBar::SDK::Vector (In Future)
			public:
				IndexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const std::vector<unsigned short>& indicies);
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			public:
				unsigned int GetIndexBufferOffset() const;
				unsigned int GetIndiciesCount() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
				unsigned int Offset = 0u;
				unsigned int Count = 0u;
			};
		}
	}
}