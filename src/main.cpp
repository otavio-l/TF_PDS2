#include <iostream>
#include <nlohmann/json.hpp>
#include "game.hpp"


int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::logic_error& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error on assets or configuration files: " << e.what() << "\n";
        return 1;
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON malformed: " << e.what();
        return 1;
    }
    catch (const nlohmann::json::type_error& e) {
        std::cout << "Wrong field type in JSON file: '" << e.what();
        return 1;
    } 
    catch (const nlohmann::json::out_of_range& e) {
        std::cout << "Missing field in JSON file: '" << e.what();
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
