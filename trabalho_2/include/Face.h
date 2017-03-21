#ifndef FACE_H
#define FACE_H

#include "GameObject.h"
#include "Sprite.h"

class Face : public GameObject {
	private:
		int m_hitpoints;
		Sprite m_sp;

	public:
		Face(int x, int y);
		
		void damage(int damage);
		void update(float dt);
		void render();
		bool is_dead();
};

#endif