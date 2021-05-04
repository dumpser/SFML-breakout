#include "game.h"
#include <iostream>
#include <tuple>
#include <algorithm>
#include <time.h>
#include "game_object.h"
#include "game_clock.h"
#include "level_creator.h"
#include "resource_manager.h"
#include "text.h"

Game::Game(unsigned int width, unsigned int height, const sf::String& title)
	: m_title{ title }, m_windowWidth{ width }, m_windowHeight{ height }, m_state{ GameState::START }, m_window{ sf::VideoMode(width, height), title }
{
	m_window.setVerticalSyncEnabled(true);

	srand(time(NULL));

	int bat = rand() % 5;
	int ball = rand() % 6;


	std::string bats[5] = { "resimler/Bats/bat_black.png", "resimler/Bats/bat_blue.png","resimler/Bats/bat_orange.png", "resimler/Bats/bat_pink.png", "resimler/Bats/bat_yellow.png" };
	std::string balls[6] = { "resimler/Balls/ball_blue.png", "resimler/Balls/ball_green.png","resimler/Balls/ball_orange.png", "resimler/Balls/ball_red.png", "resimler/Balls/ball_silver.png" , "resimler/Balls/ball_yellow.png" };

	ResourceManager::loadTextureWall("wall1", "resimler/Walls/brick.png");
	ResourceManager::loadTextureWall("wall2", "resimler/Walls/brick_blue.png");
	ResourceManager::loadTextureWall("wall3", "resimler/Walls/brick_pink_side.png");
	ResourceManager::loadTextureWall("wall4", "resimler/Walls/brick_red.png");


	ResourceManager::loadTextureBrick("resimler/Bricks/brick_blue_small.png", "resimler/Bricks/brick_blue_small.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_blue_small_cracked.png", "resimler/Bricks/brick_blue_small_cracked.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_green_small.png", "resimler/Bricks/brick_green_small.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_green_small_cracked.png", "resimler/Bricks/brick_green_small_cracked.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_pink_small.png", "resimler/Bricks/brick_pink_small.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_pink_small_cracked.png", "resimler/Bricks/brick_pink_small_cracked.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_violet_small.png", "resimler/Bricks/brick_violet_small.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_violet_small_cracked.png", "resimler/Bricks/brick_violet_small_cracked.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_yellow_small.png", "resimler/Bricks/brick_yellow_small.png");
	ResourceManager::loadTextureBrick("resimler/Bricks/brick_yellow_small_cracked.png", "resimler/Bricks/brick_yellow_small_cracked.png");

	ResourceManager::loadTexture("paddle", bats[bat]);
	ResourceManager::loadTextureBall("ball", balls[ball]);

	//ResourceManager::loadText("start", "Press SPACE to start", "arial.ttf");
	//ResourceManager::getText("start").center(sf::Vector2f((float)m_windowWidth, (float)m_windowHeight));

	//ResourceManager::loadText("continue", "Press RETURN to continue", "arial.ttf");
	//ResourceManager::getText("continue").center(sf::Vector2f((float)m_windowWidth, (float)m_windowHeight));

	m_paddle.setTexture(ResourceManager::getTexture("paddle"));
	m_paddle.setPosition(width / 2 - m_paddle.getSize().x / 2, height - 10.0f - m_paddle.getSize().y);



	m_ball.setTexture(ResourceManager::getTexture("ball"));

	m_objects = LevelCreator::create();

	m_entities.push_back(&m_paddle);
	m_entities.push_back(&m_ball);
	m_entities.push_back(&ResourceManager::getText("start"));
}

Game::~Game()
{
	ResourceManager::unloadResources();
}

void Game::pollEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::processInput(float delta)
{
	pollEvents();

	if (m_state == GameState::START || m_state == GameState::OVER)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_ball.setAttached(false);
			m_state = GameState::PLAY;

			std::vector<Entity*>::iterator it = std::find_if(m_entities.begin(), m_entities.end(), [&](Entity* e) { return &ResourceManager::getText("start") == e; });
			if (it != m_entities.end())
				m_entities.erase(it);
		}
	}
	
	if (m_state != GameState::PAUSE)
	{
		const sf::Vector2f& paddlePos = m_paddle.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddlePos.x > 10.0f)
				m_paddle.setPosition(paddlePos.x - m_paddle.getVelocity() * delta, paddlePos.y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddlePos.x < 590.0f - m_paddle.getSize().x)
				m_paddle.setPosition(paddlePos.x + m_paddle.getVelocity() * delta, paddlePos.y);
		}
	}

	if (m_state == GameState::PLAY)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_state = GameState::PAUSE;
			m_window.setTitle(m_title + " - paused");
			m_entities.push_back(&ResourceManager::getText("continue"));
		}
	}

	if (m_state == GameState::PAUSE)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_state = GameState::PLAY;
			m_window.setTitle(m_title);

			std::vector<Entity*>::iterator it = std::find_if(m_entities.begin(), m_entities.end(), [&](Entity* m) { return &ResourceManager::getText("continue") == m; });
			if (it != m_entities.end())
				m_entities.erase(it);
		}
	}
}

bool Game::checkCollision(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2)
{
	bool collisionX = rec1.getPosition().x + m_ball.getSize() >= rec2.getPosition().x && rec1.getPosition().x <= rec2.getPosition().x + rec2.getSize().x;
	bool collisionY = rec1.getPosition().y <= rec2.getPosition().y + rec2.getSize().y && rec1.getPosition().y + m_ball.getSize() >= rec2.getPosition().y;

	return collisionX && collisionY;
}

std::tuple<bool, Direction, sf::Vector2f> Game::checkCollision(const sf::CircleShape& circle, const sf::RectangleShape& rec)
{
	const sf::Vector2f circleCenter = sf::Vector2f(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());
	const sf::Vector2f recHalfSize = sf::Vector2f(rec.getSize().x / 2, rec.getSize().y / 2);
	const sf::Vector2f recCenter = sf::Vector2f(rec.getPosition().x + recHalfSize.x, rec.getPosition().y + recHalfSize.y);

	const sf::Vector2f centerDiff = circleCenter - recCenter;
	const sf::Vector2f clamped = clamp(centerDiff, -recHalfSize, recHalfSize);

	const sf::Vector2f closest = recCenter + clamped;
	const sf::Vector2f closestDiff = closest - circleCenter;

	if (sqrt(closestDiff.x * closestDiff.x + closestDiff.y * closestDiff.y) < circle.getRadius())
		return std::make_tuple(true, getDirection(closestDiff), closestDiff);
	else
		return std::make_tuple(false, Direction::TOP, sf::Vector2f(0.0f, 0.0f));
}

void Game::update(float delta)
{
	if (m_ball.isAttached())
	{
		m_ball.setPosition(m_paddle.getPosition().x + m_paddle.getSize().x / 2 - m_ball.getRadius(), m_paddle.getPosition().y - m_ball.getSize());
	}
	else
	{
		m_ball.setPosition(m_ball.getPosition().x + m_ball.getVelocity().x * delta, m_ball.getPosition().y + m_ball.getVelocity().y * delta);

		const sf::Vector2f ballPos = m_ball.getPosition();
		const sf::Vector2f ballPosTopRight = sf::Vector2f(ballPos.x + m_ball.getSize(), ballPos.y);
		const sf::Vector2f ballPosBottomLeft = sf::Vector2f(ballPos.x, ballPos.y + m_ball.getSize());
		const sf::Vector2f ballPosBottomRight = sf::Vector2f(ballPos.x + m_ball.getSize(), ballPos.y + m_ball.getSize());

		// check window boundaries for ball
		if (ballPosTopRight.x >= m_windowWidth - 10)
			m_ball.setXVelocity(-1 * abs(m_ball.getVelocity().x));
		else if (ballPos.x <= 10.0f)
			m_ball.setXVelocity(abs(m_ball.getVelocity().x));
		if (ballPos.y <= 0.0f)
			m_ball.setYVelocity(abs(m_ball.getVelocity().y));
		else if (ballPos.y > m_windowHeight + 25.0f)
		{
			m_ball.setAttached(true);
			m_state = GameState::OVER;
			m_ball.setYVelocity(-1 * abs(m_ball.getVelocity().y));
		}

		// check if ball has contact with player paddle
		std::tuple<bool, Direction, sf::Vector2f> coll = checkCollision(m_ball.getDrawable(), m_paddle.getDrawable());
		if (std::get<collisionHappened>(coll))
		{
			Direction dir = std::get<collisionDirection>(coll);
			const sf::Vector2f& diffVec = std::get<collisionPosition>(coll);
			if (dir == Direction::TOP)
			{
				m_ball.setPosition(ballPos.x, ballPos.y - abs(diffVec.y));
				m_ball.setYVelocity(-1 * abs(m_ball.getVelocity().y));
			}
			else if (dir == Direction::LEFT || dir == Direction::RIGHT)
			{
				m_ball.setXVelocity(-m_ball.getVelocity().x);

				if (dir == Direction::LEFT)
					m_ball.setPosition(ballPos.x - abs(diffVec.x), ballPos.y);
				else
					m_ball.setPosition(ballPos.x + abs(diffVec.x), ballPos.y);
			}
		}

		// check if ball hit a box
		for (size_t i = 0; i < m_objects.size() - 280; )
		{
			std::tuple<bool, Direction, sf::Vector2f> coll = checkCollision(m_ball.getDrawable(), m_objects.at(i).getDrawable());
			if (std::get<collisionHappened>(coll))
			{
				Direction dir = std::get<collisionDirection>(coll);
				const sf::Vector2f& diffVec = std::get<collisionPosition>(coll);
				if (dir == Direction::TOP || dir == Direction::BOTTOM)
				{
					m_ball.setYVelocity(-m_ball.getVelocity().y);
					float correction = m_ball.getRadius() - abs(diffVec.y);
					if (dir == Direction::TOP)
						m_ball.setPosition(ballPos.x, ballPos.y - correction);
					else
						m_ball.setPosition(ballPos.x, ballPos.y + correction);
				}
				else
				{
					m_ball.setXVelocity(-m_ball.getVelocity().x);
					float correction = m_ball.getRadius() - abs(diffVec.x);
					if (dir == Direction::LEFT)
						m_ball.setPosition(ballPos.x - correction, ballPos.y);
					else
						m_ball.setPosition(ballPos.x + correction, ballPos.y);
				}

				if (m_objects.at(i).isDestroyable())
				{
					m_objects.erase(m_objects.begin() + i);
				}
				else
				{
					if (m_objects.at(i).getType() == 1)
						m_objects.at(i).setType(BlockType::brick_blue_small_cracked);
					if (m_objects.at(i).getType() == 3)
						m_objects.at(i).setType(BlockType::brick_green_small_cracked);
					if (m_objects.at(i).getType() == 5)
						m_objects.at(i).setType(BlockType::brick_pink_small_cracked);
					if (m_objects.at(i).getType() == 7)
						m_objects.at(i).setType(BlockType::brick_violet_small_cracked);
					if (m_objects.at(i).getType() == 9)
						m_objects.at(i).setType(BlockType::brick_yellow_small_cracked);
					i++;
				}
			}
			else
			{
				i++;
			}
		}
	}
}

void Game::draw()
{
	m_window.clear();

	for (GameObject& rec : m_objects)
		m_window.draw(rec.getDrawable());

	for (const Entity* entity : m_entities)
		m_window.draw(entity->getDrawable());

	m_window.display();
}

void Game::run()
{
	GameClock clock;

	while (m_window.isOpen())
	{
		clock.update();
		processInput(clock.delta());

		if (m_state != GameState::PAUSE)
		{
			update(clock.delta());

			if (clock.readyToTick())
			{
				std::cout << clock.getFps() << std::endl;
				clock.tick();
			}
		}
		draw();
	}
}
