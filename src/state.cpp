#include "state.h"
#include "sprite.h"
#include "face.h"
#include "vector.h"

State::State() : m_requested_quit(false) {
    m_bg = new Sprite();
    m_tile_set = new TileSet(64, 64, "res/img/tileset.png");
    m_tile_map = new TileMap("res/map/tileMap.txt", m_tile_set);
}

State::~State() {
    delete(m_bg);

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
                int random_angle = rand() % 360;
                double angle = (random_angle) * acos(-1) / 180.0;

                Vector new_point(mouse_x, mouse_y);

                new_point.translate(200, 0);
                new_point.rotate(angle, Vector(mouse_x, mouse_y));

                add_object(new_point.get_x(), new_point.get_y());
            }
        }
    }
}

void State::add_object(int mouse_x, int mouse_y) {
    Face* face = new Face(mouse_x, mouse_y);

    m_objects_array.emplace_back(unique_ptr<GameObject>(face));
}

bool State::quit_requested(){
    return m_requested_quit; 
}

void State::update(float dt){
    input();

    for(auto it = m_objects_array.begin(); it < m_objects_array.end(); ++it) {
        if((*it)->is_dead()) {
            m_objects_array.erase(it);
        }
    }
}

void State::render(){
    m_bg->render(0, 0);
    m_tile_map->render(0, 0);

    for(auto& object : m_objects_array) {
        object->render();
    }
}

void State::load_assets(){
    m_bg->open("res/img/ocean.jpg");
}
