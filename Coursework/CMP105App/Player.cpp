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

	// newtonian model motion
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
	if (!overlap) return; // redundancy to ensure there is valid overlap

	// historical data
	float oldBottom = m_previousPos.y + playerCollider.size.y;
	float tileTop = otherCollider.position.y;

	// floor landing check? (base was above tile)
	if (oldBottom <= tileTop){

		// falling begins, but it hits ground
		if (m_velocity.y > 0)
		{
			m_velocity.y = 0;
			setPosition({ getPosition().x, collider.getPosition().y - getSize().y });
			m_isOnGround = true;
		}
	}
	// wall handler
	else {

		m_velocity.x *= -COEFF_RESTITUTION; // bounce off
		// fix with MTV
		if (playerCollider.position.x < otherCollider.position.x)
			setPosition({ getPosition().x - overlap->size.x, getPosition().y });
		else
			setPosition({ getPosition().x + overlap->size.x, getPosition().y });
	}
	

}
