#include <iostream>
#include "libhttp.h"

int main() {
	std::cout << "Hello World Test" << std::endl;
	// HTTPS
	//httplib::Client cli("https://dummy.restapiexample.com");
	httplib::Client cli("https://google.com");


	if (httplib::Result res = cli.Get("/")) {
		int statusCode = res->status;
		//res->body;
		std::cout << statusCode << std::endl;

	}
	
	return 0;
}