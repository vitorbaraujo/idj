#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.h"

class GameObject {
	public:
		virtual ~GameObject() {}

		virtual void update(float dt) = 0;
		virtual void render() = 0;
		virtual bool is_dead() = 0;

		Rect m_box;
};

#endif