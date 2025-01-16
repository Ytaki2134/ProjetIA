
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "Globals.h"
#include "SampleScene.h"
#include "PVZScene.h"
#include "RugbyScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	float windowWidth = WINDOWWIDTH;
	float windowHeight = WINDOWHEIGHT;

	pInstance->CreateWindow(windowWidth, windowHeight, "PVZ", 60, sf::Color::Black);
	
	pInstance->LaunchScene<RugbyScene>();

	return 0;
}