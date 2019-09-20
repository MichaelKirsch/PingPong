#pragma  once

#include "SFML/Graphics.hpp"
#include <experimental/random>
#include <iostream>
#define REPRODUCTION_THRESHOLD 18

class Person {
public:
    Person(sf::Vector2f position,int maxAge, int strength,int reproductionBonus);
    Person(sf::Vector2f position,int maxAge, int strength,int reproductionBonus,bool mutation);
    ~Person();
    void update();
    sf::Vector3i getColor();
    int getAge(){ return age;};
    void reproduce();
    int getStrength() const { return strength;};
    bool isAlive(){return alive;};
    void kill();
    int getReproductionValue(){return reproductionValue;};
    bool checkReproduction();
    int getreproductionBonus() { return reproductionBonus;};
    sf::Vector2f getPosition() const { return position;};
    void setPosition(sf::Vector2f new_position);
    void mutate();
private:
    void scan();
    void reproduction();
    int reproductionValue;
    int reproductionBonus;
    sf::Vector2f position;
    bool alive;
    int age;
    int maxAge;
    int strength;
    sf::Vector3i color;
};


