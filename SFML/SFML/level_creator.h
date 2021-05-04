#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "game_object.h"

class LevelCreator
{
public:
	static std::vector<GameObject> create()
	{
		std::vector<std::string> level { "012342", "230110","432103", "321440", "143224" };

		std::vector<GameObject> gameObjects;

		int x = 0, y = 0;

		srand(time(NULL));

		for (int i = 0 ; i< level.size(); i++)
		{
			x = 0;
			
			for (auto ch : level[i])
			{
				GameObject rec;

				switch (ch)
				{
				case '0':
					rec.setType(BlockType::brick_blue_small);
					break;
				case '1':
					rec.setType(BlockType::brick_green_small);
					break;
				case '2':
					rec.setType(BlockType::brick_pink_small);
					break;
				case '3':
					rec.setType(BlockType::brick_violet_small);
					break;
				case '4':
					rec.setType(BlockType::brick_yellow_small);
					break;
				default:
					std::cout << "Block type unknown" << std::endl;
					continue;
					break;
				}

				rec.setPosition(x * rec.getSize().x, y * rec.getSize().y);
				gameObjects.push_back(rec);
				x++;
			}
			y++;
		}


		for (int i = 0; i < 60; i++)
		{
			int randwall = rand() % 4 + 1;
			GameObject rec;
			if(randwall == 1)
				rec.setType(BlockType::wall1);
			if (randwall == 2)
				rec.setType(BlockType::wall2);
			if (randwall == 3)
				rec.setType(BlockType::wall3);
			if (randwall == 4)
				rec.setType(BlockType::wall4);
			rec.setPosition(i * 10, 0);
			gameObjects.push_back(rec);
		}

		for (int i = 0; i < 60; i++)
		{
			int randwall = rand() % 4 + 1;
			GameObject rec;
			if (randwall == 1)
				rec.setType(BlockType::wall1);
			if (randwall == 2)
				rec.setType(BlockType::wall2);
			if (randwall == 3)
				rec.setType(BlockType::wall3);
			if (randwall == 4)
				rec.setType(BlockType::wall4);
			rec.setPosition(i * 10, 790);
			gameObjects.push_back(rec);
		}

		for (int i = 0; i < 80; i++)
		{
			int randwall = rand() % 4 + 1;
			GameObject rec;
			if (randwall == 1)
				rec.setType(BlockType::wall1);
			if (randwall == 2)
				rec.setType(BlockType::wall2);
			if (randwall == 3)
				rec.setType(BlockType::wall3);
			if (randwall == 4)
				rec.setType(BlockType::wall4);
			rec.setPosition(0, i * 10);
			gameObjects.push_back(rec);
		}

		for (int i = 0; i < 80; i++)
		{
			int randwall = rand() % 4 + 1;
			GameObject rec;
			if (randwall == 1)
				rec.setType(BlockType::wall1);
			if (randwall == 2)
				rec.setType(BlockType::wall2);
			if (randwall == 3)
				rec.setType(BlockType::wall3);
			if (randwall == 4)
				rec.setType(BlockType::wall4);
			rec.setPosition(590, i * 10);
			gameObjects.push_back(rec);
		}



		return gameObjects;
	}
};
