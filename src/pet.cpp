#include "../includes/pet.h"
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
void init_pet(std::vector<Pet> &all_pets) {
  std::string pets_name{};
  std::string pets_type{};
  std::cout << "Input pets name: ";
  std::getline(std::cin >> std::ws, pets_name);
  std::cout << "Input pets type: ";
  std::getline(std::cin >> std::ws, pets_type);
  Pet new_pet = {pets_name, pets_type};
  all_pets.push_back(new_pet);
}
void Pet::feed() {
  std::cout << "You fed the pet!\n";
  happiness += 1;
  fullness += 1;
  std::cout << "Pets fullness is at " << fullness << " now.\n";
  std::cout << "Pets happiness is at " << happiness << " now.\n";
}
void Pet::play() {
  std::cout << "You played with the pet!\n";
  happiness += 1;
  energy -= 10;
  std::cout << "Pets happiness is at " << happiness << " now.\n";
  std::cout << "Pets energy is at " << energy << " now.\n";
}
void Pet::sleep() {
  std::cout << "Pet is asleep now !\n";
  energy = 100;
  std::cout << "Energy restored back to " << energy << '\n';
}
void Pet::display_stats() {
  std::cout << name << "'s"
            << " fullness is at " << fullness << " now.\n";
  std::cout << name << "'s"
            << " happiness is at " << happiness << " now.\n";
  std::cout << name << "'s"
            << " energy is at " << energy << " now.\n";
}
void Pet::save_to_file() {
  std::string file_name{"pet_data.txt"};
  std::fstream file_object(file_name, std::ios::app);
  if (!file_object.is_open()) {
    throw std::runtime_error("Could not open the file!\n");
    return;
  }
  file_object << "name " << name << '\n';
  file_object << "type " << type << '\n';
  file_object << "fullness " << fullness << '\n';
  file_object << "happiness " << happiness << '\n';
  file_object << "energy " << energy << '\n';
  file_object.close();
}
void Pet::load_state_from_file() {
  std::string file_name{"pet_data.txt"};
  std::fstream file_object(file_name);
  if (!file_object.is_open()) {
    throw std::runtime_error("Could not open the file.");
    return;
  }

  std::string line{};
  while (std::getline(file_object, line)) {
    std::istringstream iss(line);
    std::string attribute;

    if (iss >> attribute) {
      if (attribute == "name") {
        iss >> name;
      } else if (attribute == "type") {
        iss >> type;
      } else if (attribute == "fullness") {
        iss >> fullness;
      } else if (attribute == "happiness") {
        iss >> happiness;
      } else if (attribute == "energy") {
        iss >> energy;
      }
    }
  }

  file_object.close();
}