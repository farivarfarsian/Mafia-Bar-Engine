#include "Mesh.h"

void MafiaBar::Engine::Mesh::Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices)
{
	mVertices = Vertices;
	mIndices = Indices;
}

void MafiaBar::Engine::Mesh::Initialize(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material)
{
	mVertices = Vertices;
	mIndices = Indices;
	mMaterial = Material;
}

void MafiaBar::Engine::Mesh::Initialize(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices)
{
	mVertices = std::move(Vertices);
	mIndices = std::move(Indices);
}

void MafiaBar::Engine::Mesh::InitializeFromFile(const char* MeshPath)
{
	std::string MeshFileExtention = MafiaBar::Engine::filesystem::GetFileExtension(MeshPath);
	
	if (MeshFileExtention == "obj")
	{
		ReadObj(MeshPath);
	}
	else if (MeshFileExtention == "fbx")
	{
		ReadFBX(MeshPath);
	}
}

MafiaBar::Engine::Material* MafiaBar::Engine::Mesh::GetMeshMaterial() const
{
	return mMaterial;
}

const char* MafiaBar::Engine::Mesh::GetMeshPath() const
{
	return mMeshPath;
}

const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> MafiaBar::Engine::Mesh::GetVertices() const
{
	return mVertices;
}

const MafiaBar::SDK::Vector<unsigned short> MafiaBar::Engine::Mesh::GetIndices() const
{
	return mIndices;
}
