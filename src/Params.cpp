/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Parse Params
*/
#include <cstddef>
#include <cstring>
#include <iostream>
#include "../inc/Params.hpp"

Params::Params(int ac, char **av) : _verbose(false), _nbArgs(ac), _av(av), _width(1080), _height(720)
{
}

bool	Params::getVerbose() const
{
	return _verbose;
}

bool	Params::getFullscreen() const
{
	return _fullscreen;
}

bool	Params::getVsync() const
{
	return _vsync;
}

int	Params::getIndex()
{
	int	i = 0;

	while (_av[i] != NULL) {
		if (strcmp(_av[i], "--size") == 0 || strcmp(_av[i], "-s") == 0) {
			return (i);
		}
		i = i + 1;
	}
	return (0);
}

void	Params::displayHelp() const
{
	std::cerr << "USAGE:" << std::endl;
	std::cerr << "\t\t" << _av[0] << " [options]" << std::endl << std::endl;
	std::cerr << "Here is the list of diferents options : " <<std::endl;
	std::cerr << std::endl;
	std::cerr << "\t\t-s or --size [width] [height]\tSet window dimensions" << std::endl;
	std::cerr << "\t\t-v or --verbose\t\t\tPrint all object's informations (position and others)" << std::endl;
	std::cerr << "\t\t-f or --fullscreen\t\tUse the fullscreen option" << std::endl;
	std::cerr << "\t\t-f or --vsync\t\t\tUse Sync the printing of scene" << std::endl;
}

bool	Params::argsExist(const char *arg) const
{
	for (int count = 0; count < _nbArgs; ++count) {
		if (!strcmp(arg, _av[count])) {
			return true;
		}
	}
	return false;
}

bool	Params::parse()
{
	if (argsExist("-v") || argsExist("--verbose"))
		_verbose = true;
	if (argsExist("-f") || argsExist("--fullscreen"))
		_fullscreen = true;
	if (argsExist("--vsync"))
		_vsync = true;
	if (argsExist("-h") || argsExist("--help")) {
		displayHelp();
		return false;
	}
	if (argsExist("-s") || argsExist("--size")) {
		_width = atoi(_av[getIndex() + 1]);
		_height = atoi(_av[getIndex() + 2]);
		if (_width  <= 0 || _height <= 0) {
			std::cerr << "width and height , both of them must";
			std::cout << " be positive integers" << std::endl;
			return 84;
		}
	}
	return true;
}

std::pair<size_t, size_t>	Params::getResolution() const
{
	return std::make_pair(_width, _height);
}