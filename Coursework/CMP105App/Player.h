#pragma once
#include "Framework/GameObject.h"
class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    // setters for flag & lever pointers
    void setLever(GameObject* in) { m_lever = in; };
    void setFlag(GameObject* in1, GameObject* in2) { m_flagT = in1; m_flagB = in2; };
private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_previousPos;
    bool m_isOnGround = false;

    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
    const float JUMP_FORCE = 6.0f;
    const float COEFF_RESTITUTION = 0.8f;

    GameObject* m_lever; // interactive lever
    GameObject* m_flagT; // top of flag
    GameObject* m_flagB; // bottom of flag

};

