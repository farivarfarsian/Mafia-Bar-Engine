#include "Mesh.h"

MafiaBar::Engine::Mesh::Mesh(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices) 
{
	mVertexBuffer = std::make_unique<MafiaBar::Engine::Graphics::VertexBuffer>(Vertices);
	mIndexBuffer = std::make_unique<MafiaBar::Engine::Graphics::IndexBuffer>(Indices);
}

MafiaBar::Engine::Mesh::Mesh(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices, MafiaBar::SDK::Vector<unsigned short>&& Indices)
{
	mVertexBuffer = std::make_unique<MafiaBar::Engine::Graphics::VertexBuffer>(std::move(Vertices));
	mIndexBuffer = std::make_unique<MafiaBar::Engine::Graphics::IndexBuffer>(std::move(Indices));
}

MafiaBar::Engine::Mesh::Mesh(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices, const MafiaBar::SDK::Vector<unsigned short>& Indices, Material* Material)
	: mMaterial(Material)
{
	mVertexBuffer = std::make_unique<MafiaBar::Engine::Graphics::VertexBuffer>(Vertices);
	mIndexBuffer = std::make_unique<MafiaBar::Engine::Graphics::IndexBuffer>(Indices);
}

MafiaBar::Engine::Mesh::Mesh(const char* MeshPath)
	: mMeshPath(MeshPath)
{
	std::string MeshFileExtention = MafiaBar::Engine::filesystem::GetFileExtension(MeshPath);
	
	if (MeshFileExtention == "obj")
	{
		ReadObj(MeshPath); 

		//Creating Vertex And Index Buffers
	}
	else if (MeshFileExtention == "fbx")
	{
		ReadFBX(MeshPath);

		//Creating Vertex And Index Buffers
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

MafiaBar::Engine::Graphics::IndexBuffer* MafiaBar::Engine::Mesh::GetIndexBuffer() const
{
	return mIndexBuffer.get();
}

MafiaBar::Engine::Graphics::VertexBuffer* MafiaBar::Engine::Mesh::GetVertexBuffer() const
{
	return mVertexBuffer.get();
}

inline const unsigned int MafiaBar::Engine::Mesh::GetIndicesCount() const
{
	return mIndexBuffer->GetIndiciesCount();
}
