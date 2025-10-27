#include "swpch.h"
#include "Entity.h"

namespace Swallow {

	Entity::Entity(entt::entity entity_handle, Scene* scene)
		:m_entity_handle(entity_handle), m_scene(scene)
	{
	}
}