#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "httplib.h"

int main() {
    std::cout << "Hello World Test\n";

    httplib::SSLClient cli("dummy.restapiexample.com", 443);

    auto res = cli.Get("/api/v1/employees");


    std::cout << "Status: " << res->status << "\n";
    std::cout << "Body:\n" << res->body << "\n";

    return 0;
}