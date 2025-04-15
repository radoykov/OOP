#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Animal
{
private:
    /**
     * @field name - Name of the animal
     * @field age - Age of the animal
     * @field weight - Weight of the animal
     * @field isHungry - Indicates if the animal is hungry
     */
    string name;
    int age;
    double weight;
    bool isHungry;

public:
    /**
     * @brief Constructor for Animal class
     * @param name Name of the animal
     * @param age Age of the animal (must be non-negative)
     * @param weight Weight of the animal (must be non-negative)
     * @throws invalid_argument if age or weight is negative, or if name is empty
     * @note The constructor initializes the animal's hunger status to false.
     *       It is assumed that the animal is not hungry when created.
     *       The constructor checks for valid input and throws exceptions if any
     * */
    Animal(const string &name, int age, double weight)
    {
        setName(name);
        setAge(age);
        setWeight(weight);

        isHungry = false;
    }

    /**
     * @brief Getters for Animal class
     * @return The name, age, weight, and hunger status of the animal
     */
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    double getWeight() const
    {
        return weight;
    }
    bool getHungerStatus() const
    {
        return isHungry;
    }

    /**
     * @brief Setters for Animal class
     * @param name New name for the animal (must not be empty)
     * @param age New age for the animal (must be non-negative)
     * @param weight New weight for the animal (must be non-negative)
     * @throws invalid_argument if name is empty, or if age or weight is negative
     * @note The setters check for valid input and throw exceptions if any
     */
    void setName(const string &name)
    {
        if (name.length() == 0)
        {
            throw invalid_argument("Name cannot be empty.");
        }
        this->name = name;
    }
    void setAge(int age)
    {
        if (age < 0)
        {
            throw invalid_argument("Age cannot be negative.");
        }
        this->age = age;
    }
    void setWeight(double weight)
    {
        if (weight < 0)
        {
            throw invalid_argument("Weight cannot be negative.");
        }
        this->weight = weight;
    }

    /**
     * @brief Feed and sleep methods for Animal class
     * @note The feed method sets the hunger status to false, indicating the animal is not hungry.
     *       The sleep method sets the hunger status to true, indicating the animal is hungry.
     */
    void feed()
    {
        isHungry = false;
    }
    void sleep()
    {
        isHungry = true;
    }
};

class Dog : public Animal
{
private:
    /**
     * @field breed - Breed of the dog
     * @field isGoodBoy - The dog's behavior status (default is true)
     */
    string breed;
    bool isGoodBoy = true;

public:
    /**
     * @brief Constructor for Dog class
     * @param name Name of the dog (must not be empty)
     * @param age Age of the dog (must be non-negative)
     * @param weight Weight of the dog (must be non-negative)
     * @param breed Breed of the dog (must not be empty)
     * @throws invalid_argument if age, weight, or breed is invalid
     */
    Dog(const string &name, int age, double weight, const string &breed)
        : Animal(name, age, weight)
    {
        setBreed(breed);
    }

    /**
     * @brief Dog-specific methods
     * @note The bark method prints "Woof!" to the console.
     *       The wagTail method prints "Dog is wagging its tail!" to the console.
     */
    void bark() const
    {
        cout << "Woof!" << endl;
    }
    void wagTail() const
    {
        cout << "Dog is wagging its tail!" << endl;
    }

    /**
     * @brief Getters for Dog class
     * @return The breed of the dog
     */
    string getBreed() const
    {
        return breed;
    }

    /**
     * @brief Setters for Dog class
     * @param breed New breed for the dog (must not be empty)
     * @throws invalid_argument if breed is empty
     */
    void setBreed(const string &breed)
    {
        if (breed.length() == 0)
        {
            throw invalid_argument("Breed cannot be empty.");
        }
        this->breed = breed;
    }
};

class Cat : public Animal
{
private:
    /**
     * @field isIndoor - Indicates if the cat is an indoor cat
     * @field livesLeft - Number of lives left for the cat (default is 9)
     */
    bool isIndoor;
    int livesLeft = 9;

public:
    /**
     * @brief Constructor for Cat class
     * @param name Name of the cat (must not be empty)
     * @param age Age of the cat (must be non-negative)
     * @param weight Weight of the cat (must be non-negative)
     * @param isIndoor Indicates if the cat is an indoor cat
     * @throws invalid_argument if age, weight, or name is invalid
     */
    Cat(const string &name, int age, double weight, bool isIndoor)
        : Animal(name, age, weight)
    {
        setIsIndoor(isIndoor);
    }

    /**
     * @brief Cat-specific methods
     * @note The meow method prints "Meow!" to the console.
     *       The purr method prints "Cat is purring..." to the console.
     */
    void meow()
    {
        cout << "Meow!" << endl;
    }
    void purr()
    {
        cout << "Cat is purring..." << endl;
    }

    /**
     * @brief Getters for Cat class
     * @return The indoor status and lives left for the cat
     */
    bool getIsIndoor()
    {
        return isIndoor;
    }

    /**
     * @brief Setters for Cat class
     * @param isIndoor New indoor status for the cat
     */
    void setIsIndoor(bool isIndoor){
        this->isIndoor = isIndoor;
    }

    /**
     * @brief Get the number of lives left for the cat
     * @return The number of lives left for the cat
     */
    int getLivesLeft(){
        return livesLeft;
    }
};