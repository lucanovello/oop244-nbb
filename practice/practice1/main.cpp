#include <iostream>

using namespace std;



class Animal {

public:

    virtual void makeSound() { cout << "Generic animal sound" << endl; }

};



class Dog : public Animal {

public:

    void makeSound() override { cout << "Woof" << endl; }

};



class Cat : public Animal {

public:

    void makeSound() override { cout << "Meow" << endl; }

};



void playSound(Animal* a) {

    a->makeSound();

}



int main() {

    Animal* animals[] = { new Dog(), new Cat(), new Animal() };

    for (int i = 0; i < 3; ++i) {

        playSound(animals[i]);

    }

    for (int i = 0; i < 3; ++i) {

        delete animals[i];

    }

    return 0;

}