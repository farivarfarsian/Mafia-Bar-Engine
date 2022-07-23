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
			~MeshComponent();

			//Note: All of them are inlined because we don't want to move the variables twice to effect the performance. (First From MeshComponent::Initialize() and then to Mesh::Initialize())
		public:
			inline MeshComponent(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material);
			inline MeshComponent(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices);
			inline MeshComponent(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices);
			inline MeshComponent(Mesh* Mesh);
			inline MeshComponent(const char* MeshPath);
			void Run() override;
		public:
			const char* GetName() const override;
			Mesh* GetMesh() const;
		private:
			Mesh* Mesh = nullptr;
		};
	}
}