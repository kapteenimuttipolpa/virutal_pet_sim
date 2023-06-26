#include <stdexcept>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest.h"
#include "../includes/pet.h"
#include <string>
#include <vector>
#include <sstream>
#include <exception>

TEST_CASE("Test init_pet function")
{   
    SUBCASE("Test valid pet name and type"){
        std::stringstream user_input{};
        std::vector<Pet> all_pets{};

        // simulating user input
        user_input << "Boris\n";
        user_input << "Rabbit\n";
        std::cin.rdbuf(user_input.rdbuf());
        init_pet(all_pets);

        REQUIRE(all_pets.size() == 1);
        CHECK(all_pets[0].name == "Boris");
        CHECK(all_pets[0].type == "Rabbit");
    }
    SUBCASE("Test empty input"){
        std::stringstream user_input{};
        std::vector<Pet> all_pets{};
        user_input << '\n';
        user_input << '\n';
        std::cin.rdbuf(user_input.rdbuf());
        CHECK_THROWS_AS(init_pet(all_pets), std::invalid_argument);
    }
}
TEST_CASE("Test pet functions"){
    Pet new_pet;
    new_pet.name = "boris";
    new_pet.type = "rabbit"; 
    SUBCASE("Test initial values"){
        CHECK(new_pet.name == "boris");
        CHECK(new_pet.type == "rabbit");
        CHECK(new_pet.happiness == 0);
        CHECK(new_pet.fullness == 0);
        CHECK(new_pet.energy == 100);
    }
    SUBCASE("Test feeding"){
        new_pet.feed();
        CHECK(new_pet.happiness == 1);
        CHECK(new_pet.fullness == 1);
        new_pet.feed();
        new_pet.feed();
        CHECK(new_pet.happiness == 3);
        CHECK(new_pet.fullness == 3);
    }
    SUBCASE("Test playing"){
        new_pet.play();
        CHECK(new_pet.energy == 90);
        CHECK(new_pet.happiness == 1);
        new_pet.play();
        new_pet.play();
        CHECK(new_pet.energy == 70);
        CHECK(new_pet.happiness == 3);
    }
    SUBCASE("Test sleeping"){
        new_pet.play();
        new_pet.sleep();
        CHECK(new_pet.energy == 100);
    }
}
TEST_CASE("Test displaying stats"){
    Pet new_pet;
    new_pet.name = "boris";
    new_pet.type = "rabbit";
       SUBCASE("Test initial stats") {
        std::stringstream output_stream;
        std::streambuf* original_cout_buf = std::cout.rdbuf();  // Save the original cout buffer
        // redirect cout to the output stringstream
        std::cout.rdbuf(output_stream.rdbuf());
        // call the function
        new_pet.display_stats();
        // restore cout original buffer
        std::cout.rdbuf(original_cout_buf);
        // get the generated output from the output stringstream
        std::string generated_output = output_stream.str();
        //compare outputs
        std::string expected_output = "boris's fullness is at 0 now.\nboris's happiness is at 0 now.\nboris's energy is at 100 now.\n";
        CHECK_EQ(generated_output, expected_output);
    }
    SUBCASE("test updated stats"){
        new_pet.feed();
        new_pet.play();
        std::stringstream output_stream;
        std::streambuf* original_cout_buf = std::cout.rdbuf();  // save the original cout buffer
        // redirect cout to the stringstream
        std::cout.rdbuf(output_stream.rdbuf());
        // call the function under test
        new_pet.display_stats();
        // restore cout original buffer
        std::cout.rdbuf(original_cout_buf);
        //get the generated output from the output stringstream
        std::string generated_output = output_stream.str();
        // compare the generated output with the expected output
        std::string expected_output = "boris's fullness is at 1 now.\nboris's happiness is at 2 now.\nboris's energy is at 90 now.\n";
        CHECK_EQ(generated_output, expected_output);
    }
}
TEST_CASE("Test writing to file"){
    Pet new_pet;
    new_pet.name = "bob";
    new_pet.type = "the builder";
    new_pet.fullness = 10;
    new_pet.happiness = 10;
    new_pet.energy = 100;
    new_pet.unique_iq = 2;
    new_pet.save_file_name = std::to_string(new_pet.unique_iq)+new_pet.name+".txt";
    //new_pet.save_file_name is pets unique id + pets name + .txt so every pet has unique save file
    Pet another_pet;
    another_pet.name = "marco";
    another_pet.type = "polo";
    new_pet.unique_iq = 3;
    another_pet.save_file_name = std::to_string(another_pet.unique_iq)+another_pet.name+".txt";

    SUBCASE("Test writing to new file")
    {
        std::string new_file_name = "wheelbarrowinstructionsfordummies.txt"; 
        CHECK_NOTHROW(new_pet.save_to_file(new_file_name)); //Program should make the file if it doesnt exist yet
    }
    SUBCASE("Test reading data from the file")
    {
        new_pet.energy = 5;
        new_pet.save_to_file(new_pet.save_file_name);
        new_pet.energy = 90;
        new_pet.load_state_from_file(new_pet.save_file_name);
        CHECK(new_pet.name == "bob");
        CHECK(new_pet.energy == 5);
    }
    SUBCASE("Test that program takes latest save"){
        new_pet.energy = 50;
        new_pet.save_to_file(new_pet.save_file_name);
        new_pet.energy = 60;
        new_pet.save_to_file(new_pet.save_file_name);
        new_pet.energy = 0;
        CHECK(new_pet.energy == 0);
        new_pet.load_state_from_file(new_pet.save_file_name);
        CHECK(new_pet.energy == 60);
    }
    SUBCASE("Test reading with multiple pets"){
        another_pet.happiness = 1;
        new_pet.happiness = 0;
        another_pet.save_to_file(another_pet.save_file_name);
        new_pet.save_to_file(new_pet.save_file_name);
        another_pet.name = "tempname";
        new_pet.name = "tempname2";
        another_pet.load_state_from_file(another_pet.save_file_name);
        new_pet.load_state_from_file(new_pet.save_file_name);
        CHECK(another_pet.name == "marco");
        CHECK(new_pet.name == "bob");
        CHECK(another_pet.happiness == 1);
        CHECK(new_pet.happiness == 0);
    }
}
