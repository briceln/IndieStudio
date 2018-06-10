/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Created by asianpw,
*/

#include "../inc/Bomberman.hpp"
#include "../inc/keyCodes.hpp"
#include "../inc/PlayerMove.hpp"
#include "../inc/Ia.hpp"
#include "../inc/Time.hpp"

Bomberman::Bomberman(bool _verbose, size_t nbPlayer, size_t nbIa) : _verbose(_verbose), _cameraPos({500.0f, 400.0f, 225.0f}), _cameraRot({ 120.0f, 0.0f, 225.0f}), _map(nbPlayer, nbIa)
{
	currentTime = getCurrentTime();
	player.x = 30;
	player.y = 30;
	playerrotate.x = 0;
	playerrotate.y = 70;
	ia.x = 30;
	ia.y = 380;
	_models.insert({"player", { {player.x, player.y}, {0, 70}, "texture/characters/ziggs.png", "texture/characters/ziggs.md3", irr::scene::EMAT_STAND, false, true }});
	_models.insert({"player2", { {ia.x, ia.y}, {0, 70}, "texture/characters/ziggs_general.png", "texture/characters/ziggs.md3", irr::scene::EMAT_STAND, false, true }});
	_models.insert({"player3", { {380, 380}, {0, 70}, "texture/characters/ziggs_general.png", "texture/characters/ziggs.md3", irr::scene::EMAT_STAND, false, true }});
	_models.insert({"player4", { {380, 30}, {0, 70}, "texture/characters/ziggs_general.png", "texture/characters/ziggs.md3", irr::scene::EMAT_STAND, false, true }});
}

std::map<std::string, Data> &Bomberman::getModels()
{
	return _models;
}

std::map<std::string, Data> &Bomberman::getGuis()
{
	return _guis;
}

std::vector<std::vector<char>> &Bomberman::getMap()
{
	return _map.getMap();
}

Tools::vector3d &Bomberman::getCameraPos()
{
	return _cameraPos;
}

Tools::vector3d &Bomberman::getCameraRot()
{
	return _cameraRot;
}

void Bomberman::compute(std::pair<int, std::string> &events)
{
	long	now = getCurrentTime();

	if (now - currentTime > 1000) {
		Ia B('B', _map.getMap());
		Ia C('C', _map.getMap());
		Ia D('D', _map.getMap());
		B.start();
		C.start();
		D.start();
		checkBomb();
		currentTime = now;
	}
}

IScene *Bomberman::newScene()
{
	return nullptr;
}

void	Bomberman::bombExplode(Position p)
{
	int	x = 1;
	std::vector<std::vector<char>> &map = getMap();
	bool	top = false;
	bool	bot = false;
	bool	right = false;
	bool	left = false;

	map = _map.getMap();
	map[p.x][p.y] = ' ';
	while (x < 3)
	{
		if ((p.x + x) < 15 && map[p.x + x][p.y] != '*' && !top)
		{
			if (map[p.x + x][p.y] >= 49 && map[p.x + x][p.y] <= 51)
				bombExplode({p.x + x, p.y});
			if (map[p.x + x][p.y] != ' ')
				top = true;
			map[p.x + x][p.y] = ' ';
		}
		if ((p.x - x) > 0 && map[p.x - x][p.y] != '*' && !bot)
		{
			if (map[p.x - x][p.y] >= 49 && map[p.x - x][p.y] <= 51)
				bombExplode({p.x - x, p.y});
			if (map[p.x - x][p.y] != ' ')
				bot = true;
			map[p.x - x][p.y] = ' ';
		}
		if ((p.y + x) < 15 && map[p.x][p.y + x] != '*' && !right)
		{
			if (map[p.x][p.y + x] >= 49 && map[p.x][p.y + x] <= 51)
				bombExplode({p.x, p.y + x});
			if (map[p.x][p.y + x] != ' ')
				right = true;
			map[p.x][p.y + x] = ' ';
		}
		if ((p.y - x) > 0 && map[p.x][p.y - x] != '*' && !left)
		{
			if (map[p.x][p.y - x] >= 49 && map[p.x][p.y - x] <= 51)
				bombExplode({p.x, p.y - x});
			if (map[p.x][p.y - x] != ' ')
				left = true;
			map[p.x][p.y - x] = ' ';
		}
		x++;
	}
}

void Bomberman::checkBomb()
{
	int	x = 0;
	int	y;
	std::vector<std::vector<char>> &map = getMap();

	map = _map.getMap();
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			if (map[x][y] == '1')
				map[x][y] = '2';
			else if (map[x][y] == '2')
				map[x][y] = '3';
			else if (map[x][y] == '3')
				bombExplode({x, y});
			y++;
		}
		x++;
	}
}

void Bomberman::checkEvents(std::pair<int, std::string> &events)
{
	PlayerMove	p('A', _map.getMap());
	Position	place;

	if (bombDir < 0 || bombDir > 3)
		bombDir = 1;
	p.setBombDir(bombDir);
	if (events.first == KeyCode::KEY_SPACE) {
		std::cerr << "Space button to use a bomb" << std::endl;
		p.putBomb();
	}
	if (events.first == KeyCode::KEY_LEFT) {
		std::cerr << "Left direction" << std::endl;
		bombDir = 3;
		p.moveLeft();
		_models["player"].rot.y = 0;
		if (p.getStatus() == false)
			_models["player"].pos.y = _models["player"].pos.y - 30;
	}
	if (events.first == KeyCode::KEY_UP) {
		std::cerr << "Up direction" << std::endl;
		bombDir = 0;
		p.moveUp();
		_models["player"].rot.y = 90;
		if (p.getStatus() == false)
			_models["player"].pos.x = _models["player"].pos.x - 30;
	}
	if (events.first == KeyCode::KEY_RIGHT) {
		std::cerr << "Right direction" << std::endl;
		bombDir = 1;
		p.moveRight();
		_models["player"].rot.y = 180;
		if (p.getStatus() == false)
			_models["player"].pos.y = _models["player"].pos.y + 30;
	}
	if (events.first == KeyCode::KEY_DOWN) {
		std::cerr << "Down direction" << std::endl;
		bombDir = 2;
		p.moveDown();
		_models["player"].rot.y = -90;
		if (p.getStatus() == false)
			_models["player"].pos.x = _models["player"].pos.x + 30;
	}
}