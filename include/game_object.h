#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "rectangle.h"

class GameObject {
	public:
		virtual ~GameObject() {}

		virtual void update(double dt) = 0;
		virtual void render() = 0;
		virtual bool is_dead() = 0;

		Rectangle m_box;
};

#endif
