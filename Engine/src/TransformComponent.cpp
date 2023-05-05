#include "../include/TransformComponent.hpp"

TransformComponent::TransformComponent(std::string name) : m_position({128, 508}), m_roatation(0), m_scale(1),
                                                           tname(name) {
}

TransformComponent::~TransformComponent() {
}

void TransformComponent::Update() {}

void TransformComponent::Render(SDL_Renderer *renderer) {}

void TransformComponent::SetPosition(int x, int y) {
    m_position.x = x;
    m_position.y = y;
}

void TransformComponent::UnSetPosition(int caveId) {
    m_caveId = caveId;
}

void TransformComponent::SetLastPosition(int x, int y) {
    m_lastPosition.x = x;
    m_lastPosition.y = y;
}

int TransformComponent::GetLastX() { return m_lastPosition.x; }

int TransformComponent::GetLastY() { return m_lastPosition.y; }

float TransformComponent::GetX() { return m_position.x; }

float TransformComponent::GetY() { return m_position.y; }

int TransformComponent::GetCaveId() { return m_caveId; }

std::string TransformComponent::GetAnimType(){ return animName; }

// Setters
void TransformComponent::SetX(float newX) { m_position.x = newX; }

void TransformComponent::SetY(float newY) { m_position.y = newY; }

void TransformComponent::resetCaveId() { m_caveId = 0; }

std::string TransformComponent::getTname(){ return tname;}

void TransformComponent::SetAnimType(std::string animType){ animName = animType; }


std::string TransformComponent::getDetailsText() { return this->detailsTxt; }

void TransformComponent::setDetailsText(std::string text) {
    this->detailsTxt = text;
}

