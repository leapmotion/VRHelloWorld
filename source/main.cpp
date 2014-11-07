//
//  main.cpp
//  VRHello
//
//  Created by Joe Ward on 10/22/14.
//  Copyright (c) 2014 Leap Motion, Inc. All rights reserved.
//

#include "App.h"
#include <SDL.h>
#include <direct.h>

int main(int argc, char* argv[]) {
	char currentPath[FILENAME_MAX];
	printf("CWD: %s", _getcwd(currentPath, sizeof(currentPath)));
    return App::getInstance()->execute(argc, argv);
}

/*
#include <iostream>
#include <SDL.h>

int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();

	return 0;
}
*/