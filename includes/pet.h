#ifndef PET_H
#define PET_H
#include <string>
#include <vector>

struct Pet{
    std::string name;
    std::string type;
    int happiness;
    int fullness;
    int energy = 100;
    void play();
    void feed();
    void sleep();
};
void init_pet(std::vector<Pet>& all_pets);

#endif //PET_H