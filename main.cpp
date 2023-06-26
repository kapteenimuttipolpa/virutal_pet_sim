#include<iostream>
#include "./includes/pet.h"
#include <string>
#include <vector>
int main()
{
    std::vector<Pet> all_pets{};
    init_pet(all_pets);
    all_pets[0].feed();
    return 0;
}