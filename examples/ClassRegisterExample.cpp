#include <iostream>
#include <chrono>
#include <vector>

#include "anax/ObjectCreator.h"

/********************************************************************************
 * GOAL:
 * To create a random amount of objects of different types, randomly.
 *
 * Please do note, that this example requires C++11's initializer list
 * features.
 *
 * Here is some example output, of the program. 
 *
 * Creating 14 different animals of the following random types:
 * - Cat
 * - Dog
 * - Lion
 * - Tiger
 * Starting to create Animals...
 * Cat
 * Lion
 * Lion
 * Dog
 * Dog
 * Lion
 * Dog
 * Tiger
 * Dog
 * Tiger
 * Tiger
 * Cat
 * Dog
 * Tiger
 * Finished creating Animals...
 * TOOK: 0.037234ms
 *********************************************************************************/

// An abstract base-class for an Animal
class Animal
{
public:
    virtual ~Animal() {}
    virtual std::string getName() const = 0;
};

// sub classes

class Cat : public Animal
{
public:
    virtual std::string getName() const { return std::string("Cat"); }
};

class Dog : public Animal
{
public:
    virtual	std::string getName() const { return std::string("Dog"); }
};

class Lion : public Animal
{
public:
    virtual std::string getName() const { return std::string("Lion"); }
};

class Tiger : public Animal
{
public:
    virtual std::string getName() const { return std::string("Tiger"); }
};

// register the sub classes
ANAX_CLASS_REGISTER(Animal, Cat);
ANAX_CLASS_REGISTER(Animal, Dog);
ANAX_CLASS_REGISTER(Animal, Lion);
ANAX_CLASS_REGISTER(Animal, Tiger);

// generates a new random animal
Animal* generateRandomAnimal(const std::vector<std::string>& possibleRandomElements)
{
    return anax::create<Animal>(possibleRandomElements[rand() % possibleRandomElements.size()]);
}


double GetTimeNow()
{
	using std::chrono::duration;
	using std::chrono::duration_cast;
	using std::chrono::high_resolution_clock;
	
	return duration_cast<duration<double, std::ratio<1> > >(high_resolution_clock::now().time_since_epoch()).count();
}

void printTimeTaken(double start, double end)
{
	std::cout << "Took: " << (end - start) << " seconds\n";
}

int main(int argc, char* argv[])
{
    const int MAX_AMOUNT_OF_ANIMALS_TO_CREATE = 30;
    
    // seed random
    srand((unsigned int)time(NULL));
    
    const int amountOfAnimalsToCreate = rand() % MAX_AMOUNT_OF_ANIMALS_TO_CREATE + 1;
    
    // list of possible animals to generate
    std::vector<std::string> randomAnimalList = { "Cat", "Dog", "Lion", "Tiger" };
    
    std::cout << "Creating " << amountOfAnimalsToCreate << " different animals of the following random types:\n";
    
    for(auto& x : randomAnimalList)
    {
        std::cout << "- " << x << '\n';
    }
    
    std::cout << "Starting to create Animals...\n";
    
    double start = 0;
	double end = 0;
	
	start = GetTimeNow();
    for(size_t i = 0; i < amountOfAnimalsToCreate; ++i)
    {
        // generate a new random animal
        Animal* randomAnimal = generateRandomAnimal(randomAnimalList);
		
        // print out the random animal's name
        std::cout << randomAnimal->getName() << '\n';
        
        // destroy the animal (good practice)
        anax::destroy(randomAnimal);
    }
    end = GetTimeNow();
    
    std::cout << "Finished creating Animals...\n";
	printTimeTaken(start, end);
    
    return 0;
}