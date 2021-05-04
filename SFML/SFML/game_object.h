#pragma once

#include <SFML/Graphics.hpp>

enum class BlockType
{
	brick_blue_small,
	brick_blue_small_cracked,
	brick_green_small,
	brick_green_small_cracked,
	brick_pink_small,
	brick_pink_small_cracked,
	brick_violet_small,
	brick_violet_small_cracked,
	brick_yellow_small,
	brick_yellow_small_cracked,
	wall1,
	wall2,
	wall3,
	wall4
};

class GameObject
{
private:
	sf::RectangleShape m_shape;

	bool m_isDestroyable;

	int m_type;

public:
	GameObject();

	const sf::RectangleShape& getDrawable() const;

	void setPosition(float x, float y);

	const sf::Vector2f& getSize() const;

	void setType(BlockType type);

	int getType();

	bool isDestroyable() const;
};
