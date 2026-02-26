#pragma once

#include "Framework/GameObject.h" 

enum interactType { LEVER, FLAGTOP, FLAGBASE};


class InteractGameObject : public GameObject
{
public:
	void setType(enum interactType);
	enum interactType getType() { return m_interactType; };

private:
	enum interactType m_interactType;
	bool m_isTriggered = false;
};

