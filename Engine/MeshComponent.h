#pragma once
#include "Component.h"

#include "Mesh.h"

namespace MafiaBar
{
	namespace Engine
	{
		struct MB_ENGINE_API MeshComponent final : public Component
		{
			MeshComponent() = default;
			~MeshComponent() = default;

			//Initializer Methods for Initializng Mesh Instance. 
			//Note: All of them are inlined because we don't want to move the variables twice to effect the performance. (First From MeshComponent::Initialize() and then to Mesh::Initialize())
		public:
			inline void Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material = nullptr);
			inline void Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices);
			inline void Initialize(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices);
			inline void Initialize(Mesh* Mesh);
			inline void InitializeFromFile(const char* MeshPath);
		public:
			const char* GetName() const override;
			Mesh* GetMesh() const;
		private:
			Mesh* Mesh = nullptr;
		};
	}
}