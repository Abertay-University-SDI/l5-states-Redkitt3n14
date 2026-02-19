#include "Player.h"
#include <iostream>

Player::Player()
{
	if (!m_texture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad";

	setTexture(&m_texture);
	setSize({ 120,120 });
	setCollisionBox({ {40,20}, { 40,100 } });
	setPosition({ 50,0 });
	m_isOnGround = false;
	setTextureRect({ { 0,0 }, { 24,24 } });
}

void Player::handleInput(float dt)
{
	m_acceleration = { 0,0 };

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
		m_acceleration.x -= SPEED;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_acceleration.x += SPEED;

	if (m_isOnGround) { // jump only on ground
		if (m_input->isKeyDown(sf::Keyboard::Scancode::Space) || m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_velocity.y -= JUMP_FORCE;
	}

	if (m_input->isKeyDown(sf::Keyboard::Scancode::R))	// Reset (for debugging)
	{
		setPosition({ 50,0 });
		m_velocity = { 0,0 };
	}
}

void Player::update(float dt)
{
	// updates saved previous position before applying any changes
	m_previousPos = getPosition();

	// newtonian model
	m_acceleration.y += GRAVITY;
	m_isOnGround = false;
	m_velocity += dt * m_acceleration;
	move(m_velocity);

}

void Player::collisionResponse(GameObject& collider)
{
	// overlap finder & verifier
	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect otherCollider = collider.getCollisionBox();
	auto overlap = playerCollider.findIntersection(otherCollider);
	if (!overlap) return;

	if (overlap->size.x > overlap->size.y) { // is overlap wider than tall (aka on ground)

		// falling begins, but it hits ground
		if (m_velocity.y > 0)
		{
			m_velocity.y = 0;
			setPosition({ getPosition().x, collider.getPosition().y - getSize().y });
			m_isOnGround = true;
		}
	}
	else {
		m_velocity.x = 
	}
	

}
