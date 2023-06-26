#ifndef PET_H
#define PET_H
#include <string>
#include <vector>

struct Pet{
    std::string name;
    std::string type;
    int happiness;
    int fullness;
    void feed();
};
void init_pet(std::vector<Pet>& all_pets);

#endif //PET_H