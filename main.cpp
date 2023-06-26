#include "./includes/pet.h"
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
int main() {
  std::string file_name{"pet_data.txt"};
  std::vector<Pet> all_pets{};
  std::string choise{};
  Pet* current_pet = nullptr; // pointer to current pet
  std::cout << "Welcome to ur virtual pet simular!\n";
  while (true) {
    std::cout << "\nWould you like to\n(1) add a new pet\n(2) do something with "
                 "current pet\n(3)change current pet\n";
    std::getline(std::cin >> std::ws, choise);
    if(choise == "1"){
        init_pet(all_pets);
    }
    else if(choise == "2"){
        if(current_pet == nullptr){
            std::cout << "Please choose a pet first.\n";
            continue;
        }
        ui_loop(current_pet);
    }
    else if(choise == "3"){
        current_pet = change_current_pet(all_pets, current_pet);

    }
    else if(choise == "q" or choise == "Q"){
        std::exit(EXIT_SUCCESS);
    }
    else{
        std::cout << "Unknown command.\n";
        continue;
    }
  }

  return 0;
}