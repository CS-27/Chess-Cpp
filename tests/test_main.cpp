// test_main.cpp
#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp> // For Catch2 v3 and later

int main(int argc, char* argv[]) {
    Catch::Session session; // Create a Catch2 session
    int result = session.run(argc, argv); // Run the tests
    // You can add custom code here before or after running tests
    // e.g., setup or teardown operations, or additional program logic
    return result;
}