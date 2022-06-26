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
				/// <summary>
				///  Replaces the Passed IndexBuffer Instance with the already existing one, It replaces the IndexBuffer, Indices, Offset and Indices Count.
				///  Note: This Method needs Improvement for the third parameter, Perphaps IndexBuffer class could hold the Indices in it in the future.
				/// </summary>
				void Replace(Graphics& Graphics, const IndexBuffer& IndexBuffer, const MafiaBar::SDK::Vector<unsigned short>& Indices);
			public:
				ID3D11Buffer* GetIndexBuffer() const;
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