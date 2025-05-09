#include "Transition.hpp"
#include <Vector.h>

Transition::Transition(State<Transition>* source, State<Transition>* target)
    : source(source)
    , target(target)
{
    this->source->addOutgoingTransition(this);
};

Transition::~Transition()
{
}

void Transition::setSync(event e)
{
    this->sync = e;
};

// void Transition::setSource(State<Transition>* s){
//   this->source = s;
//   s->addOutgoingTransition(this);
// };
// void Transition::setTarget(State<Transition>* s){
//   this->target = s;
// };

bool Transition::isEnabled(event e)
{
    return this->sync == e;
};

void Transition::setTrigger(char trigger)
{
    this->trigger = trigger;
};

char Transition::getTrigger()
{
    return this->trigger;
};

bool Transition::isTrigger(char e)
{
    // Serial.println("debugging isTrigger() ");
    // Serial.print("before comp: ");
    // Serial.println(this -> getTrigger());
    // bool comp = this -> trigger == e;
    // Serial.print("after comp: ");
    // Serial.println(this -> getTrigger());
    // return comp;
    return this->trigger == e;
};

State<Transition>* Transition::getTarget()
{
    return this->target;
};

State<Transition>* Transition::getSource()
{
    return this->source;
}