#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "httplib.h"

int main() {
	// HTTPS
	httplib::Client cli("http://localhost:5062");

	// /players/1
	// /players/1000001
	std::string playerRoute = "/players/";
	std::string clientId = "2";
	
	if (auto res = cli.Post((playerRoute + clientId), "{\"name\": \"Chandler\", \"clientId\": \"2\"}", "text/json")) {
		std::cout << res->status << " " << res->body << std::endl;
	}

    auto res = cli.Get("/api/v1/employees");


    std::cout << "Status: " << res->status << "\n";
    std::cout << "Body:\n" << res->body << "\n";

    return 0;
}