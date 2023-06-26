#include<iostream>
#include "./includes/pet.h"
#include <string>
#include <vector>
int main()
{
    std::vector<Pet> all_pets{};
    init_pet(all_pets);
    all_pets[0].feed();
    all_pets[0].play();
    all_pets[0].sleep();
    all_pets[0].display_stats();
    all_pets[0].save_to_file();
    return 0;
}