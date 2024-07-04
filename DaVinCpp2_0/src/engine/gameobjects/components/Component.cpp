#include "Component.h"

namespace davincpp
{
	Component::Component(ComponentType uniqueType)
		: m_UniqueType(uniqueType)
	{ }


	ComponentType Component::getUniqueType() const
	{
		return m_UniqueType;
	}
}
