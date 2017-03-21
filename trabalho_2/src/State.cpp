#include "State.h"
#include "Sprite.h"
#include "Face.h"

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
			printf("fechooou\n");
			m_requested_quit = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) {
			printf("clicou\n");	
			int size = m_objects_array.size();

			printf("size: %d\n", size);
			for(int i = size - 1; i >= 0; i--) {
				Face* face = (Face *) m_objects_array[i].get();

				// fazer is_inside em Rect
				// if(face->m_box.is_inside((float)mouse_x, (float)mouse_y)) {
				// 	face->damage(rand() % 10 + 10);
				// 	break;
				// }
			}
		}

		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				printf("fechou no esc\n");
				m_requested_quit = true;
			}
			else {
				printf("adding object in mouse: {%d, %d}\n", mouse_x, mouse_y);
				add_object((float)mouse_x, (float)mouse_y);
			}
		}
	}
}

void State::add_object(float mouse_x, float mouse_y) {
	// 200 pixels de distancia
	printf("cria face\n");
	Face* face = new Face(mouse_x, mouse_y);
	printf("cria emplace\n");
	m_objects_array.emplace_back(unique_ptr<GameObject>(face));
	printf("fim add_object\n");
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
