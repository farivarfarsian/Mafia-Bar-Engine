#include "MeshComponent.h"

MafiaBar::Engine::MeshComponent::~MeshComponent()
{
	if (Mesh != nullptr)
	{
		delete Mesh;
	}
}

inline MafiaBar::Engine::MeshComponent::MeshComponent(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material)
{
	Mesh = new MafiaBar::Engine::Mesh(Vertices, Indices, Material);
}

inline MafiaBar::Engine::MeshComponent::MeshComponent(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices)
{
	Mesh = new MafiaBar::Engine::Mesh(Vertices, Indices);
}

inline MafiaBar::Engine::MeshComponent::MeshComponent(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices)
{
	Mesh = new MafiaBar::Engine::Mesh(std::move(Vertices), std::move(Indices));
}

inline MafiaBar::Engine::MeshComponent::MeshComponent(MafiaBar::Engine::Mesh* Mesh)
{
	this->Mesh = Mesh;
}

inline MafiaBar::Engine::MeshComponent::MeshComponent(const char* MeshPath)
{
	Mesh = new MafiaBar::Engine::Mesh(MeshPath);
}

void MafiaBar::Engine::MeshComponent::Run()
{
	if (Mesh != nullptr)
	{
		Mesh->GetVertexBuffer()->Bind();
		Mesh->GetIndexBuffer()->Bind();
	}
}

const char* MafiaBar::Engine::MeshComponent::GetName() const
{
	return "Mesh";
}

MafiaBar::Engine::Mesh* MafiaBar::Engine::MeshComponent::GetMesh() const
{
	return Mesh;
}
