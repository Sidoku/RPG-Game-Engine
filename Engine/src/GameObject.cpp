#include "../include/GameObject.hpp"

GameObject::GameObject(){
}

GameObject::~GameObject(){

}

void GameObject::AddComponent(Component* component) {
    m_components.push_back(component);
}

void GameObject::Update() {
    for(auto component : m_components){
        component->Update();
    }
}

void GameObject::Render(SDL_Renderer* renderer) {
    for(auto component : m_components){
        component->Render(renderer);
    }
}

