#pragma once
//This is a base class for the agents


namespace AI
{

	//Entity has a reference of our wolrd the navegation system witch is the GridBased graph
	class AIWorld;
	class Entity;
	using EntitiesPtrs = std::vector<Entity*>;

	class Entity
	{

	public:

		Entity(AIWorld& world, uint32_t typeId);
		virtual ~Entity();

		//Do not allow copy
		Entity(const Entity&) = delete;
		Entity(const Entity&&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(const Entity&&) = delete;
		

		AIWorld& world;//reference of the world

		//Position - pixel position represented inside our wolrd
		float posX = 0.0f;
		float posY = 0.0f;

		//Direction ai is looking at / where our character is point to
		float headingX  = 0.0f;
		float headingY = 1.0f;
		//-----> x
		//^ + Y

		//represent the size / how thick is our entity or agent
		float radius = 1.0f;

		uint32_t GetTypeID() const { return static_cast<uint32_t>(mUniqueID >> 32);}
		uint64_t GetUniqueID() const { return mUniqueID;}

	private:

		//each agent has to have it own ID
		const uint64_t mUniqueID = 0;
	};

}

//Note Agente is going to be a child of entity
//This guy is going to have a velocity, speed, mass, endPoint(destination)
