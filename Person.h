#pragma  once

#include "SFML/Graphics.hpp"
#include <experimental/random>
#define REPRODUCTION_THRESHOLD 30

class Person {
public:
    Person();
    ~Person();
    void update();
    sf::Vector3i getColor(){return color;};
    int getAge(){ return age;};
    int getStrength(){ return strenth;};
    bool isAlive(){return alive;};
    void kill();
    int getReproductionValue(){return reproductionValue;};
    bool checkReproduction();
    sf::Vector2i getPosition(){ return position;};
    void setPosition(sf::Vector2i new_position);
private:
    void scan();
    void reproduction();
    int reproductionValue;
    sf::Vector2i position;
    bool alive;
    int age;
    int strenth;
    sf::Vector3i color;
};


