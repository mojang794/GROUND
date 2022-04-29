#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace gr {
	class Component;
	class Entity;
	class Manager;

	using ComponentID = std::size_t;

	inline ComponentID getNewComponentTypeID()
	{
		static ComponentID lastID = 0u;
		return lastID++;
	}

	template <typename T> inline ComponentID getComponentTypeID() noexcept
	{
		static_assert (std::is_base_of<Component, T>::value, "");
		static ComponentID typeID = getNewComponentTypeID();
		return typeID;
	}

	constexpr std::size_t maxComponents = 32;
	constexpr std::size_t maxGroups = 32;

	using ComponentBitSet = std::bitset<maxComponents>;

	using ComponentArray = std::array<Component*, maxComponents>;

	class Component
	{
	public: 
		Entity* entity;

		virtual void init() {}
		virtual void update(float deltatime __attribute__((unused))) {}
		virtual void draw() {}
		virtual void destroyGL() {}
		virtual ~Component() {}
	};

	class Entity
	{
	private:
		Manager& manager;
		bool active = true;
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitset;

	public:
		Entity(Manager& mManager) : manager(mManager) {}

		void update(float deltatime)
		{
			for (auto& c : components) c->update(deltatime);
		}
		void draw() 
		{
			for (auto& c : components) c->draw();
		}
		void destroyGL()
		{
			for (auto& c : components) c->destroyGL();
		}

		bool isActive() const { return active; }
		void destroy() { active = false; }

		template <typename T> bool hasComponent() const
		{
			return componentBitset[getComponentTypeID<T>()];
		}

		template <typename T, typename... TArgs>
		T& addComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component>uPtr { c };
			components.emplace_back(std::move(uPtr));

			componentArray[getComponentTypeID<T>()] = c;
			componentBitset[getComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		template<typename T> T& getComponent() const
		{
			auto ptr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}
	};

	class Manager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	public:
		void update(float dt)
		{
			for (auto& e : entities) e->update(dt);
		}
		void draw()
		{
			for (auto& e : entities) e->draw();
		} 
		void refresh()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity> &mEntity)
			{
				return !mEntity->isActive();
			}),
				std::end(entities));
		}
		void destroyGL()
		{
			for (auto& e : entities) e->destroyGL();
		}

		Entity& addEntity()
		{
			Entity *e = new Entity(*this);
			std::unique_ptr<Entity> uPtr { e };
			entities.emplace_back(std::move(uPtr));
			return *e;
		}
	};
}