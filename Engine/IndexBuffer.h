#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API IndexBuffer : public Bindable
			{
			public:		
				IndexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::SDK::Vector<unsigned short>& indices);
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