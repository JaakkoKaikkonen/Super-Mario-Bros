#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Tile.hpp"
#include "Mario.hpp"
#include "BrickTile.hpp"
#include "BoxTile.hpp"
#include "Pipe.hpp"
#include "Game.hpp"
#include "Decoration.hpp"
#include "Pole.hpp"
#include "DEFINITIONS.hpp"
#include "Enemy.hpp"
#include "Goomba.hpp"
#include "Koopa.hpp"
#include "Piranha.hpp"
#include "Score.hpp"
#include "Money.hpp"
#include "Platform.hpp"


namespace engine {

	int loadLevel(std::string filePath, std::vector<Tile*>& levelTiles, std::vector<Enemy*>& enemies, std::vector<Decoration>& levelDecorations, Mario& mario, std::vector<Money>& money, Pole& pole, Castle& castle, std::vector<Score>& scores,
				int& coins, gameDataRef data) {

		std::ifstream inputFile(filePath);

		if (inputFile.is_open()) {
			
			std::string line;
			int y = 0;

			while (inputFile >> line) {

				for (int x = 0; x < line.length(); x++) {
					if (line[x] != '.') {
						if (line[x] == 'G') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, GROUND_TILE, data));
						} else if (line[x] == 'H') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, GROUND_TILE_BLUE, data));
						} else if (line[x] == 'B') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::empty, Setting::OW, coins, scores, data));
						} else if (line[x] == '£') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, Setting::OW, coins, scores, data));
						} else if (line[x] == 'N') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::empty, Setting::UG, coins, scores, data));
						} else if (line[x] == '%') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, Setting::UG, coins, scores, data));
						} else if (line[x] == '¤') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::powerUp, Setting::UG, coins, scores, data));
						} else if (line[x] == '?') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, Setting::OW, coins, scores, data));
						} else if (line[x] == '&') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::powerUp, Setting::OW, coins, scores, data));
						} else if (line[x] == '!') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, Setting::UG, coins, scores, data));
						} else if (line[x] == '|') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::powerUp, Setting::UG, coins, scores, data));
						} else if (line[x] == '<') {
							levelTiles.emplace_back(new Platform(x * TILE_SIZE, y * TILE_SIZE, mario, data));
						} else if (line[x] == 'S') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, STAIR_TILE, data));
						} else if (line[x] == 'D') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, STAIR_TILE_UG, data));
						} else if (line[x] == 'p') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_BOTTOM, mario, false, data));
						} else if (line[x] == 'P') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_TOP, mario, false, data));
						} else if (line[x] == '½') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_TOP, mario, true, data));
						} else if (line[x] == 'å') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_BOTTOM_UG, mario, false, data));
						} else if (line[x] == 'Å') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_TOP_UG, mario, false, data));
						} else if (line[x] == '1') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_TOP_UG, mario, true, data));
						} else if (line[x] == '€') {
							money.emplace_back(Money(x * TILE_SIZE, y * TILE_SIZE, Setting::OW, data));
						} else if (line[x] == '$') {
							money.emplace_back(Money(x * TILE_SIZE, y * TILE_SIZE, Setting::UG, data));
						} else if (line[x] == 'c') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", CLOUD_TILE1, data));
						} else if (line[x] == 'C') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", CLOUD_TILE2, data));
						} else if (line[x] == '+') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", CLOUD_TILE3, data));
						} else if (line[x] == '-') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", BUSH_TILE1, data));
						} else if (line[x] == '=') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", BUSH_TILE2, data));
						} else if (line[x] == '_') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", BUSH_TILE3, data));
						} else if (line[x] == '~') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", BUMP_TILE_SMALL, data));
						} else if (line[x] == '@') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Tiles", BUMP_TILE_BIG, data));
						} else if (line[x] == '#') {
							levelDecorations.emplace_back(Decoration(x * TILE_SIZE, y * TILE_SIZE, "Castle", SMALL_CASTLE, data));
						} else if (line[x] == 'g') {
							enemies.emplace_back(new Goomba(x * TILE_SIZE, y * TILE_SIZE, Setting::OW, scores, data));
						} else if (line[x] == 'u') {
							enemies.emplace_back(new Goomba(x * TILE_SIZE, y * TILE_SIZE, Setting::UG, scores, data));
						} else if (line[x] == 'k') {
							enemies.emplace_back(new Koopa(x * TILE_SIZE, y * TILE_SIZE, Setting::OW, scores, data));
						} else if (line[x] == 'l') {
							enemies.emplace_back(new Koopa(x * TILE_SIZE, y * TILE_SIZE, Setting::UG, scores, data));
						} else if (line[x] == 'v') {
							enemies.emplace_back(new Piranha(x * TILE_SIZE, y * TILE_SIZE, Setting::OW, scores, data));
						} else if (line[x] == 'V') {
							enemies.emplace_back(new Piranha(x * TILE_SIZE, y * TILE_SIZE, Setting::UG, scores, data));
						} else if (line[x] == '§') {
							castle.setPosition(x * TILE_SIZE, y * TILE_SIZE, SMALL_CASTLE, CASTLE_FLAG);
						} else if (line[x] == 'O') {
							pole.setPosition(x * TILE_SIZE, y * TILE_SIZE);
						} else if (line[x] == 'M') {
							mario.position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
						}
					}
				}
				y++;
			}

			std::cout << "Map loaded" << std::endl;
			return line.length();
		} else {
			std::cout << "Map not loaded" << std::endl;
			exit(EXIT_SUCCESS);
		}

		
	}



}