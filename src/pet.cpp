#include "../includes/pet.h"
#include <string>
#include <iostream>

void init_pet(std::vector<Pet>& all_pets)
{
    std::string pets_name{};
    std::string pets_type{};
    std::cout << "Input pets name: ";
    std::getline(std::cin >> std::ws, pets_name);
    std::cout << "Input pets type: ";
    std::getline(std::cin >> std::ws, pets_type);
    Pet new_pet = {pets_name, pets_type};
    all_pets.push_back(new_pet);
}
void Pet::feed(){
    std::cout << "You fed the pet!\n";
    happiness+= 1;
    fullness+= 1;
    std::cout << "Pets fullness is at " << fullness << " now.\n";
    std::cout << "Pets happiness is at " << happiness << " now.\n";
}
void Pet::play(){
    std::cout << "You played with the pet!\n";
    happiness+= 1;
    energy -= 10;
    std::cout << "Pets happiness is at " << happiness << " now.\n";
    std::cout << "Pets energy is at " << energy << " now.\n";
}
void Pet::sleep(){
    std::cout << "Pet is asleep now !\n";
    energy = 100;
    std::cout << "Energy restored back to " << energy << '\n';
}
void Pet::display_stats(){
    std::cout << name << "'s"<<" fullness is at " << fullness << " now.\n";
    std::cout << name << "'s"<<" happiness is at " << happiness << " now.\n";
    std::cout << name << "'s"<<" energy is at " << energy << " now.\n";
}