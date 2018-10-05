#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Tile.hpp"
#include "BrickTile.hpp"
#include "BoxTile.hpp"
#include "Pipe.hpp"
#include "Game.hpp"
#include "Decoration.hpp"
#include "Pole.hpp"
#include "DEFINITIONS.hpp"


namespace engine {

	int loadLevel(std::vector<Tile*>& levelTiles, std::vector<Decoration>& levelDecorations, Pole& pole, Castle& castle, std::string filePath, gameDataRef data) {

		std::ifstream inputFile(filePath);

		if (inputFile.is_open()) {
			
			std::string line;
			int y = 0;

			while (inputFile >> line) {

				for (int x = 0; x < line.length(); x++) {
					if (line[x] != '.') {
						if (line[x] == 'G') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, GROUND_TILE, data));
						} else if (line[x] == 'B') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::empty, data));
						} else if (line[x] == '$') {
							levelTiles.emplace_back(new BrickTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, data));
						} else if (line[x] == '?') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::coin, data));
						} else if (line[x] == '^') {
							levelTiles.emplace_back(new BoxTile(x * TILE_SIZE, y * TILE_SIZE, Items::mushroom, data));
						} else if (line[x] == 'S') {
							levelTiles.emplace_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, STAIR_TILE, data));
						} else if (line[x] == 'P') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_TOP, data));
						} else if (line[x] == 'p') {
							levelTiles.emplace_back(new Pipe(x * TILE_SIZE, y * TILE_SIZE, PIPE_BOTTOM, data));
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
						} else if (line[x] == '§') {
							castle.setPosition(x * TILE_SIZE, y * TILE_SIZE, SMALL_CASTLE, CASTLE_FLAG);
						} else if(line[x] == 'O') {
							pole.setPosition(x * TILE_SIZE, y * TILE_SIZE);
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




	void constrain(float& value, float min, float max) {
		if (value < min) {
			value = min;
		} else if (value > max) {
			value = max;
		}
	}


}