#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "gui.h"
#include "search.h"
#include "data.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	class that act as the game engine
	wrapper class
*/

class Game{
	private:
		//variables
		//window
		sf::VideoMode videoMode;
		sf::RenderWindow* window;
		sf::Event evnt; 
		sf::Vector2i mousePosWindow;
		Search *search;
		sf::Font font;
		gui::Button* submitBtn;
		gui::TextBox* inputField;
		gui::TextBox* outputField;
		Data data;
		gui::DropDownList *fromList;
		gui::DropDownList *toList;
		
		//private functions
		void initVariables();
		void initWindow();
		void initSearch();
		void initFont();
		void initSubmitBtn();
		void initField();
		void initDropDown();
	public:
		//constructors & destructors
		Game();
		virtual ~Game();
		
		//accessors
		const bool running();
		
		//functions	
		void updateMousePos();
		void searching();
		void pollEvents();
		void update();
		void render();
};

#endif
