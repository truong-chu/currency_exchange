#include "game.h"
#include <iostream>

//private functions
void Game::initVariables(){
	this->window = nullptr;
}

void Game::initWindow(){
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	
	this->window = new sf::RenderWindow(this->videoMode, "Sample only", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(144);
}

void Game::initSearch(){
	this->search = new Search;
}

void Game::initFont(){
    if (!this->font.loadFromFile("Dosis-Light.ttf"))
	{
        std::cout << "error load font!\n";
	}

	this->font.loadFromFile("Dosis-Light.ttf");
}

void Game::initSubmitBtn(){
	// Submit Button
	this->submitBtn = new gui::Button(10.0, 10.0, 150.0, 45.0, &this->font, "Convert", 30, sf::Color::White, sf::Color::Red, sf::Color::White, sf::Color::Red, sf::Color::White, sf::Color::Red);

	std::cout << "Success\n";
}

void Game::initField(){
	this->inputField = new gui::TextBox(10.0, 60.0, 300.0, 45.0, &this->font,  20, sf::Color::Black, sf::Color::White, 1);

	this->outputField = new gui::TextBox(10.0, 110.0, 300.0, 45.0, &this->font,  20, sf::Color::Black, sf::Color::White, 1);
}

void Game::initDropDown(){
	// Drop down
	this->fromList = new gui::DropDownList(320.0, 60.0, 150.0, 45.0, this->font, this->data.getData(), 7, 143);
	this->toList = new gui::DropDownList(320.0, 110.0, 150.0, 45.0, this->font, this->data.getData(), 7, 147);
}

//constructors & destructors
Game::Game(){
	this->initVariables();
	this->initWindow();
	this->initSearch();
	this->initFont();
	this->initSubmitBtn();
	this->initField();
	this->initDropDown();
}

Game::~Game(){
	delete this->window;
}

//accessors
const bool Game::running(){
	return this->window->isOpen();
}

//Functions
void Game::updateMousePos(){
	/*
	@ return void
	
		Update the mouse positions:
		- Mouse position relative to the windows (vector2i)
	*/
	
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::searching(){
	if (this->search->isRunning == false) {
		this->search->render(this->inputField->getText(), this->fromList->getActiveElementValue().substr(0, 3), this->toList->getActiveElementValue().substr(0, 3));
		this->outputField->setText(this->search->response);
	}
}

void Game::pollEvents(){
    //event polling
    while (this->window->pollEvent(this->evnt)) {
        switch (this->evnt.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->evnt.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                    break;
                } 

				std::cout << this->evnt.key.code << "\n";
				if (this->evnt.key.code == 58) {
					this->searching();
					break;
				} else if (this->evnt.key.code >= 26 && this->evnt.key.code <= 35) {
					this->inputField->update(this->evnt.key.code + 22);
					break;
				} else if (this->evnt.key.code == 50) {
					if (!this->inputField->update('.')) {
						std::cout << "Error!";
					};
					break;
				} else if (this->evnt.key.code == 59) {
					if (!this->inputField->update(8)) {
						std::cout << "Error!";
					};
					break;
				} else {
					std::cout << "Error!";
					break;
				} 		
        }
    }
}

void Game::update(){
	this->pollEvents();	

	this->updateMousePos();
	this->submitBtn->update(this->mousePosWindow);
	this->fromList->update(this->mousePosWindow, 0.1);
	this->toList->update(this->mousePosWindow, 0.1);
}

void Game::render(){
	/*
		@return void
		- clear old frames
		- render new objs
		- display frame in window
		
		Render the game objs
	*/
	this->window->clear();

	this->submitBtn->render(*this->window);
	this->inputField->render(*this->window);
	this->outputField->render(*this->window);
	this->fromList->render(*this->window);
	this->toList->render(*this->window);
	//draw game objects
	this->window->display();

	if (this->submitBtn->isPressed() == true) {
		this->searching();
	}
}