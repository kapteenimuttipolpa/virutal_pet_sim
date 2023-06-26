#ifndef PET_H
#define PET_H
#include <string>
#include <vector>
#include <fstream>

struct Pet{
    std::string name;
    std::string type;
    static int unique_iq;
    int happiness = 0;
    int fullness = 0;
    int energy = 100;
    void play();
    void feed();
    void sleep();
    void display_stats();
    void save_to_file(std::string& file_name);
    void load_state_from_file(std::string& file_name);
    std::string save_file_name = std::to_string(unique_iq) + name+".txt";
};
void init_pet(std::vector<Pet>& all_pets);
Pet* change_current_pet(std::vector<Pet> &all_pets, Pet* current_pet);
void ui_loop(Pet* current_pet);
#endif //PET_H