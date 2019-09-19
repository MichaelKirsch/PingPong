
#include "Person.h"

void Person::update() {
    age++; reproductionValue++; //the person will age and get more "grown" at every tick

    //scan
    //move


    if(age>strenth)
    {
        //dies
        alive=false;
    }

    if(reproductionValue>REPRODUCTION_THRESHOLD)
    {
        //reproduction();
        reproductionValue=0;
    }



}

bool Person::checkReproduction() {
    if(reproductionValue>age)
        return true;
}
