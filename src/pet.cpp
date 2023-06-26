#include "../includes/pet.h"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
int Pet::unique_iq = 0; // unique id for pets
/**
 * @brief init_pet
    creates pet and pushes it to
    all_pets vector
 * 
 * @param all_pets 
 */
void init_pet(std::vector<Pet> &all_pets) {
  std::string pets_name{};
  std::string pets_type{};
  std::cout << "Input pets name: ";
  std::getline(std::cin >> std::ws, pets_name);
  std::cout << "Input pets type: ";
  std::getline(std::cin >> std::ws, pets_type);
  if (pets_name.empty() || pets_type.empty()) {
    throw std::invalid_argument("Name and type required.");
    return;
  }
  Pet new_pet = {pets_name, pets_type};
  new_pet.unique_iq++;
  new_pet.save_file_name = // save_file_name is the filename program creates for
  //the pet if it doesnt already exist
      std::to_string(new_pet.unique_iq) + new_pet.name + ".txt";
  all_pets.push_back(new_pet);
}
/**
 * @brief feed() feed the pet
 *  happiness and fullness increases
 */
void Pet::feed() {
  std::cout << "You fed the pet!\n";
  happiness += 1;
  fullness += 1;
  std::cout << "Pets fullness is at " << fullness << " now.\n";
  std::cout << "Pets happiness is at " << happiness << " now.\n";
}
/**
 * @brief play() plays with pet
 *  happiness increases, energy decreases
 */
void Pet::play() {
  std::cout << "You played with the pet!\n";
  happiness += 1;
  energy -= 10;
  std::cout << "Pets happiness is at " << happiness << " now.\n";
  std::cout << "Pets energy is at " << energy << " now.\n";
}
/**
 * @brief sleep() puts the pet to sleep
 *  energy goes back to 100
 */
void Pet::sleep() {
  std::cout << "Pet is asleep now !\n";
  energy = 100;
  std::cout << "Energy restored back to " << energy << '\n';
}
/**
 * @brief display_stats()
 * displays pets current stats
 */
void Pet::display_stats() {
  std::cout << name << "'s"
            << " fullness is at " << fullness << " now.\n";
  std::cout << name << "'s"
            << " happiness is at " << happiness << " now.\n";
  std::cout << name << "'s"
            << " energy is at " << energy << " now.\n";
}
/**
 * @brief save_to_file()
 *  saves pets data to file
 *  so it can be restored later
 * @param file_name 
 */
void Pet::save_to_file(std::string &file_name) {
  file_name = save_file_name;
  std::fstream file_object(file_name, std::ios::app); // add in append mode
  // so it creates new files automatically
  if (!file_object.is_open()) {
    throw std::runtime_error("Could not open the file!\n");
    return;
  }
  file_object << "id " << unique_iq << '\n';
  file_object << "name " << name << '\n';
  file_object << "type " << type << '\n';
  file_object << "fullness " << fullness << '\n';
  file_object << "happiness " << happiness << '\n';
  file_object << "energy " << energy << '\n';
  file_object.close();
}
/**
 * @brief load_state_from_file()
 * loads the last saved state
 * @param file_name 
 */
void Pet::load_state_from_file(std::string &file_name) {
  file_name = save_file_name; // save_file_name is member of Pet
  std::fstream file_object(file_name);
  if (!file_object.is_open()) {
    //throw error if file is not found
    throw std::runtime_error("Could not open the file.");
    return;
  }
  std::string line{};
  while (std::getline(file_object, line)) { //loop lines in file
    std::istringstream iss(line);
    std::string attribute;

    if (iss >> attribute) { //parse the data from lines using isstringstream
      if (attribute == "id") {
        iss >> unique_iq;
      } else if (attribute == "name") {
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
/**
 * @brief change_current_pet
 *  changes the current pet pointer to something from
 *  all pets and return pointer to the user choise
 * @param all_pets 
 * @param current_pet 
 * @return Pet* 
 */
Pet *change_current_pet(std::vector<Pet> &all_pets, Pet *current_pet) {
  if (all_pets.size() == 0) {
    std::cout << "No pets to choose from :( \n)";
    return nullptr; // return nullptr if vector is empty
  }
  while (true) {
    std::cout << "Choose from the following pets: \n";
    std::string choise{};
    for (const auto &pet : all_pets) {
      std::cout << pet.name << '\n';
    }
    //loop all_pets and if choise is found, update pointer
    //and return it
    std::getline(std::cin >> std::ws, choise);
    for (auto &pet : all_pets) {
      if (pet.name == choise) {
        current_pet = &pet;
        return current_pet;
      }
    }
    std::cout << "Invalid choise. Try again.\n";
  }
}
/**
 * @brief ui_loop()
 *  the inner ui loop to do stuff with pet
 * @param current_pet 
 */
void ui_loop(Pet *current_pet) {
  while (true) {
    int choise{};
    std::cout << "\nChoose from the following: \n";
    std::cout << "(1)Feed the pet\n(2)Play with the pet\n(3)Knock out the pet\n";
    std::cout
        << "(4)display pets stats\n(5)save game\n(6)load game\n(7)go back\n";
    std::cin >> choise;
    switch (choise) {
    case 1:
      current_pet->feed();
      break;
    case 2:
      current_pet->play();
      break;
    case 3:
      current_pet->sleep();
      break;
    case 4:
      current_pet->display_stats();
      break;
    case 5:
      current_pet->save_to_file(current_pet->save_file_name);
      break;
    case 6:
      current_pet->load_state_from_file(current_pet->save_file_name);
      break;
    case 7:
      return;
      break;
    default:
      std::cout << "Invalid command!\n";
      break;
    }
  }
}