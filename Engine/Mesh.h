#pragma once
#include "def.h"
#include "pch.h"

#include "GraphicDataTypes.h"

#include "Material.h"

#include "FileSystem.h"


#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Mesh final
		{
		public:
			Mesh() = default;
			~Mesh() = default;
			Mesh(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices);
			Mesh(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices);
			Mesh(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material);
			Mesh(const char* MeshPath);
		public:
			Material* GetMeshMaterial() const;
			const char* GetMeshPath() const;
			MafiaBar::Engine::Graphics::IndexBuffer* GetIndexBuffer() const;
			MafiaBar::Engine::Graphics::VertexBuffer* GetVertexBuffer() const;
			inline const unsigned int GetIndicesCount() const;
		public:
			static Mesh* ReadObj(const char* MeshPath) //Needs Implementation.
			{
				return nullptr;
			}
			static Mesh* ReadFBX(const char* MeshPath) //Needs Implementation.
			{
				return nullptr;
			}
		private:
			Material* mMaterial = nullptr;
			const char* mMeshPath = nullptr;
			std::unique_ptr<MafiaBar::Engine::Graphics::VertexBuffer> mVertexBuffer;
			std::unique_ptr<MafiaBar::Engine::Graphics::IndexBuffer> mIndexBuffer;
		};  //The structure is absolutely incomplete, Needs a lot more implementations and improvements will get to them when implementing the Assimp library.
	}
}
