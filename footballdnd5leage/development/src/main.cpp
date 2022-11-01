#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <ctime>

// Rolls a dX, d stand for dice, X for the number of Eyes of the dice
int rollD(int eyes)
{
    int dice = std::rand() % eyes + 1; 
    return dice;
}

// Metaclass for human
class Human 
{
    public:
        const int id; 
        std::string name;
        int age;        //[a]
        double weight;  //[kg]
        double height;  //[m]

        Human(int _id, std::string _name, int _age,
        double _weight, double _height):
            id(_id),
            name(_name),
            age(_age), 
            weight(_weight),
            height(_height)
        {}
};

// stores Attribut information. Form should mirror current player condition
// if in a bad condition, reduce form below 1. If in extraordinary form, push above 1 
class HumanAttribute 
{
    public:
        int value;
        float form = 1.0; // value between [0-2] in percent

        HumanAttribute(int attrval): value(attrval) {};
};

// Story health of a player. Per action health will be redused. Use float to mirror 
// physique of player. If injured, mark the player as injured
class HumanBodycondition 
{
    public:
        float health; // value between [0-2] In Precent
        std::string injury;
        bool injured = false;
};


class FootballPlayer: public Human 
{
    public:
        // Attributes for player. From 0 - 20.
        // Is it better to store it as pointer??? https://stackoverflow.com/questions/7557153/defining-an-object-without-calling-its-constructor-in-c
        // TODO Need to remove pointer in destructor!!
        
        HumanAttribute* dribbling;
        HumanAttribute* passing;
        HumanAttribute* shooting;
        HumanAttribute* tackling;
        HumanAttribute* interception;
        HumanAttribute* positioning;
        HumanAttribute* speed;
        HumanAttribute* strength;
        HumanAttribute* fitness;

        // goalkeeping
        HumanAttribute* g_shootstopper;
        HumanAttribute* g_arealcontrol;

        // Constructor
        FootballPlayer(int _id, 
                       std::string _name, 
                       int _age,
                       double _weight, 
                       double _height): Human(_id, _name,_age, _weight, _height) {
                            setAttributesClassic5D();
                       };

    private:

        // Rolls 4 d6 and erases the lowest of the rolls. Returns the summ of the three rolls
        //      eyes = Max eye of dice

        int roll4d6forAttr(int eyes = 6) 
        {
            
            std::vector<int> rolls = {rollD(eyes), rollD(eyes), rollD(eyes), rollD(eyes)};
            std::size_t smallidx = 0;
            int smallesVal = eyes;

            // Search for the smalles roll and remove it
            for (std::size_t i = 0; i < rolls.size(); i++)
            {
                if (rolls[i] < smallesVal) 
                {
                    smallesVal = rolls[i];
                    smallidx = i;
                }

            }

            rolls.erase(rolls.begin() + static_cast<int>(smallidx));  // vector needs iterator, thats why begin()

            int sumofrolls = 0;

            for (int i: rolls)
            {
                sumofrolls += i;
            }

            return sumofrolls;
        }

        void setAttributesClassic5D()
        {
            // Set attributes of player the dnd5 character way. Rolls 4 d6 and uses the hightes of three numbers per attribute.

            dribbling = new HumanAttribute(roll4d6forAttr());
            passing = new HumanAttribute(roll4d6forAttr());
            shooting = new HumanAttribute(roll4d6forAttr());
            tackling = new HumanAttribute(roll4d6forAttr());
            interception = new HumanAttribute(roll4d6forAttr());
            positioning = new HumanAttribute(roll4d6forAttr());
            speed = new HumanAttribute(roll4d6forAttr());
            strength = new HumanAttribute(roll4d6forAttr());
            fitness = new HumanAttribute(roll4d6forAttr());

        };
};




[[nodiscard]] auto main(int argc, char* argv[]) noexcept -> int
{
    (void)argc;
    (void)argv;

    std::srand(static_cast<unsigned int>(time(nullptr)));

    FootballPlayer footy(0,"tom", 27, 87, 170);
    std::cout << footy.dribbling->value << std::endl;
    std::cout << footy.shooting->value << std::endl;
    std::cout << footy.passing->value << std::endl;
    std::cout << footy.tackling->value << std::endl;
    std::cout << footy.interception->value << std::endl;

    footy.dribbling->value =0;
    
    std::cout << footy.dribbling->value << std::endl;
}
