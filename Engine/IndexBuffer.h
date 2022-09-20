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
				IndexBuffer(const MafiaBar::SDK::Vector<unsigned short>& indices);
				void Bind() override;
				/// <summary>
				///  Replaces the Passed IndexBuffer Instance with the already existing one, It replaces the IndexBuffer, Indices, Offset and Indices Count.
				/// </summary>
				void Replace(const IndexBuffer& IndexBuffer);
			public:
				ID3D11Buffer* GetIndexBuffer() const;
				unsigned int GetIndexBufferOffset() const;
				unsigned int GetIndiciesCount() const;
				std::vector<unsigned short> GetIndicies() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
				unsigned int Offset = 0u;
				unsigned int Count = 0u;
			};
		}
	}
}