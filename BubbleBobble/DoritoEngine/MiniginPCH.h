#pragma once


#pragma region

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

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