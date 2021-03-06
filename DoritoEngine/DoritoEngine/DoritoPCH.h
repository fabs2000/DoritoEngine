#pragma once

#pragma region

#include <stdio.h>
#include <iostream> // std::cout
#include <fstream>
#include <sstream> // stringstream
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <chrono>
#include <functional>
#include <future>
#include <array>


//SFML
#include "SFML/Graphics.hpp"

//SDL
#include <SDL_rect.h>

#pragma endregion Includes

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma region 

template<class T>
void SafeDelete(T& pObj)
{
	if (pObj != nullptr)
	{
		delete pObj;
		pObj = nullptr;
	}
}

#pragma endregion Template Functions