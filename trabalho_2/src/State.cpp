#include "State.h"
#include "Sprite.h"
#include "Face.h"

#include <utility>

using std::pair;

State::State() : m_requested_quit(false) {
    m_bg = new Sprite();
}

State::~State() {
	m_objects_array.clear();
}

void State::input() {
	SDL_Event event;
	int mouse_x, mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			m_requested_quit = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) {
			int size = m_objects_array.size();

			for(int i = size - 1; i >= 0; i--) {
				Face* face = (Face *) m_objects_array[i].get();

				// fazer is_inside em Rect
				if(face->m_box.is_inside(mouse_x, mouse_y)) {
					face->damage(rand() % 10 + 10);
					break;
				}
			}
		}

		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				m_requested_quit = true;
			}
			else {
				int random_angle = rand() % 361;
				float angle = random_angle * acos(-1) / 180.0;

				pair<int, int> C(mouse_x, mouse_y);
				pair<int, int> P(mouse_x + 200, mouse_y);
				pair<int, int> Q(P.first - C.first, P.second - C.second);

				Q = pair<int, int>(	Q.first * cos(angle) - Q.second * sin(angle),
									Q.first * sin(angle) + Q.second * cos(angle));


				Q = pair<int, int>(	Q.first + C.first, Q.second + C.second);

				add_object(Q.first, Q.second);
			}
		}
	}
}

void State::add_object(int mouse_x, int mouse_y) {
	// 200 pixels de distancia
	Face* face = new Face(mouse_x, mouse_y);

	m_objects_array.emplace_back(unique_ptr<GameObject>(face));
}

bool State::quit_requested(){
    return m_requested_quit; 
}

void State::update(float dt){
    input();

    int size = m_objects_array.size();
    for(int i = 0; i < size; i++) {
    	Face* face = (Face *)m_objects_array[i].get();

    	if(face->is_dead()) {
    		m_objects_array.erase(m_objects_array.begin() + i);
    	}
    }
}

void State::render(){
    m_bg->render(0, 0);

	for(object : m_objects_array) {
		object->render();
	}
}

void State::load_assets(){
    m_bg->open("res/img/ocean.jpg");
}
