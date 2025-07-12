// tests/test_main.cpp
#define CATCH_CONFIG_RUNNER
#include <catch2/catch_all.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    Catch::Session session;
    int result = session.run(argc, argv);
    std::cout << "Done running tests.\n";
    return result;
}