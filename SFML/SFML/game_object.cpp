#include "game_object.h"

#include <random>

#include "resource_manager.h"

std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0, 255);

GameObject::GameObject()
	: m_shape{ sf::Vector2f(100.0f, 30.0f) }
{
}

const sf::RectangleShape& GameObject::getDrawable() const
{
	return m_shape;
}

void GameObject::setPosition(float x, float y)
{
	m_shape.setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f& GameObject::getSize() const
{
	return m_shape.getSize();
}

void GameObject::setType(BlockType type)
{
	switch (type)
	{
	case BlockType::brick_blue_small:
		m_type = 1;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_blue_small.png"));
		break;
	case BlockType::brick_blue_small_cracked:
		m_type = 2;
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_blue_small_cracked.png"));
		break;
	case BlockType::brick_green_small:
		m_type = 3;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_green_small.png"));
		break;
	case BlockType::brick_green_small_cracked:
		m_type = 4;
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_green_small_cracked.png"));
		break;
	case BlockType::brick_pink_small:
		m_type = 5;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_pink_small.png"));
		break;
	case BlockType::brick_pink_small_cracked:
		m_type = 6;
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_pink_small_cracked.png"));
		break;
	case BlockType::brick_violet_small:
		m_type = 7;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_violet_small.png"));
		break;
	case BlockType::brick_violet_small_cracked:
		m_type = 8;
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_violet_small_cracked.png"));
		break;
	case BlockType::brick_yellow_small:
		m_type = 9;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_yellow_small.png"));
		break;
	case BlockType::brick_yellow_small_cracked:
		m_type = 10;
		m_isDestroyable = true;
		m_shape.setTexture(&ResourceManager::getTexture("resimler/Bricks/brick_yellow_small_cracked.png"));
		break;
	case BlockType::wall1:
		m_type = 11;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("wall1"));
		m_shape.setSize(sf::Vector2f(10, 10));
		break;
	case BlockType::wall2:
		m_type = 11;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("wall2"));
		m_shape.setSize(sf::Vector2f(10, 10));
		break;
	case BlockType::wall3:
		m_type = 11;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("wall3"));
		m_shape.setSize(sf::Vector2f(10, 10));
		break;
	case BlockType::wall4:
		m_type = 11;
		m_isDestroyable = false;
		m_shape.setTexture(&ResourceManager::getTexture("wall4"));
		m_shape.setSize(sf::Vector2f(10, 10));
		break;
	}
}

int GameObject::getType()
{
	return m_type;
}

bool GameObject::isDestroyable() const
{
	return m_isDestroyable;
}
