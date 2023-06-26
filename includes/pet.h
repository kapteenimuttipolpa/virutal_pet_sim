#ifndef PET_H
#define PET_H
#include <string>
#include <vector>
#include <fstream>

struct Pet{
    std::string name;
    std::string type;
    int happiness;
    int fullness;
    int energy = 100;
    void play();
    void feed();
    void sleep();
    void display_stats();
    void save_to_file();
    void load_state_from_file();
};
void init_pet(std::vector<Pet>& all_pets);

#endif //PET_H