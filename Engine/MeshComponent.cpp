#include "MeshComponent.h"

inline void MafiaBar::Engine::MeshComponent::Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material)
{
	Mesh->Initialize(Vertices, Indices, Material);
}

inline void MafiaBar::Engine::MeshComponent::Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices)
{
	Mesh->Initialize(Vertices, Indices);
}

inline void MafiaBar::Engine::MeshComponent::Initialize(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices)
{
	Mesh->Initialize(Vertices, Indices);
}

inline void MafiaBar::Engine::MeshComponent::Initialize(MafiaBar::Engine::Mesh* Mesh)
{
	this->Mesh = Mesh;
}

inline void MafiaBar::Engine::MeshComponent::InitializeFromFile(const char* MeshPath)
{
	Mesh->InitializeFromFile(MeshPath);
}

const char* MafiaBar::Engine::MeshComponent::GetName() const
{
	return "Mesh";
}

MafiaBar::Engine::Mesh* MafiaBar::Engine::MeshComponent::GetMesh() const
{
	return Mesh;
}
