#pragma once

#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
/*
	class that act as the game engine
	wrapper class
*/

class Search{
	private:
		//variables
        struct memory{
            char *memory;
            size_t size;
        };
		double amount;
		std::string from;
		std::string to;
		std::string url;
        
		//private functions
        static size_t writecallback(char *contents, size_t size, size_t nmemb, void *userp);
	public:
		//constructors & destructors
		Search();
		~Search();
		
		//accessors
		char *response;
		bool isRunning;
		
		//functions
		void convert();
		void toAmount(std::string money);
		char *processData(char *memory);
       	void render(std::string amount = "1.00", std::string from = "USD", std::string to = "VND");
};

#endif