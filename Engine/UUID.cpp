#include "UUID.h"

//Random UUID Generator is only locally available for UUID structure.

static std::mt19937_64 L_Engine(std::random_device{}());
static std::uniform_int_distribution<uint64_t> L_UUIDGenerator;


MafiaBar::Engine::UUID::UUID() : m_UUID(L_UUIDGenerator(L_Engine))
{

}

MafiaBar::Engine::UUID::UUID(unsigned long long UUID) : m_UUID(UUID)
{

}

MafiaBar::Engine::UUID::~UUID()
{

}

MafiaBar::Engine::UUID::operator unsigned long long() const
{
	return m_UUID;
}

MafiaBar::Engine::UUID MafiaBar::Engine::UUID::GetUUID()
{
	return (L_UUIDGenerator(L_Engine));
}
