/*
 *		Load.cpp - files load functions sources
 *
 *		Copyright 2012 Maxim Kachur <mcdebugger@duganet.ru>
 *		
 *		This file is part of Arkilloid.
 *
 *		Arkilloid is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version.
 *
 *		Arkilloid is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License
 *		along with Arkilloid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Load.h"

int LoadBrick(std::string filename) {
	filename = path_construct("images/bricks", filename);
	Texture *texture = new Texture;
	if(texture->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(texture);
	
	return true;
}

int LoadTexture(std::string filename) {
	filename = path_construct("images", filename);
	Texture *texture = new Texture;
	if(texture->load_from_file(filename) == false)
	{
		log("ERROR: " + filename + " not found");
		return false;
	}
	textureList.push_back(texture);
	
	return true;
}
