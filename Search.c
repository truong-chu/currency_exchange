#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>
#include <math.h>
#include <cmath>
#include <iostream>

#include "Search.h"

//private functions
size_t Search::writecallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    //fprintf(stderr, "Got %d bytes\n", (int)size * nmemb);
    //printf("Got %d bytes\n", (int)size * nmemb);
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);

    if(ptr == NULL){
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&mem->memory[mem->size], contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize; 
}

//constructors & destructors
Search::Search(){
    //exception handlers + url prep
    this->isRunning = false;
}

Search::~Search(){
	//delete this->window;
}

//accessors

//Functions
void Search::convert(){
    std::string amount_str = std::to_string(roundf(this->amount * 100.0) / 100.0);

    this->url = "https://www.xe.com/currencyconverter/convert/?Amount=" + amount_str + "&From=" + this->from + "&To=" + this->to;
}

void Search::toAmount(std::string money){
    this->amount = 0.0;
    int dot = -1;
    for (int i = 0; i < money.length(); i++) {
        if (money[i] == '.') {
            dot = i;
            continue;
        }
        if (dot == -1) {
            this->amount *= 10;
            this->amount += (int)((char)(money[i] - 48));
        } else {
            if (i - dot >= 3) {
                if (money[i] >= '5') {
                    this->amount += .01;
                }
                break;
            }
            this->amount += (int)((char)(money[i] - 48)) * pow(10, dot - i);
        }
    }
}

char *Search::processData(char *memory){
    isRunning = true;
    char *domain = NULL;
    int countChar = 0, start1 = 37, stop1, start2, stop2;

    domain = strstr(memory, "result__BigRate-sc-1bsijpp-1 iGrAod");

    int i = start1;
    while (countChar < 2){
        if (domain[i] == '<') {
            countChar++;
            if (countChar == 1){
                stop1 = i - 1;
            } else {
                stop2 = i - 1;
            }
        }
        if (domain[i] == '>') {
            start2 = i + 1;
        }
        i++;
    };
    int len1 = stop1 - start1 + 1, len2 = stop2 - start2 + 1;

    char *res_str = (char*)malloc(len1 + len2 + 1); 
    memcpy( res_str, &domain[start1], len1 );
    memcpy( res_str + len1, &domain[start2], len2 );
    res_str[len1 + len2] = '\0';

    FILE * fp;
    fp = fopen ("file.html", "w");
    fprintf(fp, res_str);
    fprintf(fp, "----Bengals");

    fclose(fp);
    return res_str;
}

void Search::render(std::string amount, std::string from, std::string to){
    this->toAmount(amount);
    this->from = from;
    this->to = to;
    this->convert();
    std::cout << this->amount << "\n";

    CURL *curl;
    CURLcode res;
    Search::memory chunk;
    char* response;

    chunk.memory = NULL;
    chunk.size = 0;

    //settings 
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 1);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "D:\\Personal\\new_c++\\cpp_lib\\curl-7.87.0_2-win64-mingw\\cacert.pem");
    curl_easy_setopt(curl, CURLOPT_CAPATH, "D:\\Personal\\new_c++\\cpp_lib\\curl-7.87.0_2-win64-mingw\\cacert.pem");
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->writecallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() return %s\n", curl_easy_strerror(res));
        } else {          
            this->response = this->processData(chunk.memory);
            fprintf(stderr, "Our string is %s\n", this->response);
        }

        free(chunk.memory);

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    isRunning = false;
}