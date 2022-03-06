#ifndef COMPONENT_H
#define COMPONENT_H


class Entity;


/*base class for the components. components keeps a pointer to the entity it is a component of*/

class Component {

public:

	Component() = default;

	void setEntity(Entity* e) {
		entity = e;
	}
	

	
	Entity* getEntity() const {
		return entity;
	}

	

	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

private:

	Entity* entity = nullptr;

	Component(const Component&) = delete;
	const Component& operator=(const Component&) = delete;

};
#endif