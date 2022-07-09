#pragma once
#include "def.h"
#include "pch.h"

#include "GraphicDataTypes.h"

#include "Material.h"

#include "FileSystem.h"

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Mesh final
		{
		public:
			Mesh() = default;
			~Mesh() = default;
			void Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices);
			void Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material);
			void Initialize(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices);
			void InitializeFromFile(const char* MeshPath);
		public:
			Material* GetMeshMaterial() const;
			const char* GetMeshPath() const;
			const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> GetVertices() const;
			const MafiaBar::SDK::Vector<unsigned short> GetIndices() const;
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
			MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> mVertices;
			MafiaBar::SDK::Vector<unsigned short> mIndices;
		};  //The structure is absolutely incomplete, Needs a lot more implementations and improvements will get to them when implementing the Assimp library.
	}
}
