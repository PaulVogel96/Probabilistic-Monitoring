#include "ProbTransition.hpp"

ProbTransition::ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target){
  this->source = source;
  this->source->addOutgoingTransition(this);
  this->target = target;
  this->probability = 1;
}

ProbTransition::ProbTransition(State<ProbTransition>* source, State<ProbTransition>* target, float probability){
  this->source = source;
  this->source->addOutgoingTransition(this);
  this->target = target;
  this->probability = probability;
};

ProbTransition::~ProbTransition(){}

void ProbTransition::setSync(event e){
  this->sync = e;
};

void ProbTransition::setSource(State<ProbTransition>* s){
  this->source = s;
  s->addOutgoingTransition(this);
};
void ProbTransition::setTarget(State<ProbTransition>* s){
  this->target = s;
};
bool ProbTransition::isEnabled(event e){
  return this->sync == e;
};

State<ProbTransition>* ProbTransition::getTarget(){
  return this->target;
};

State<ProbTransition>* ProbTransition::getSource(){
  return this->source;
}

void ProbTransition::setProbability(float prob){
  this->probability = prob;
}

float ProbTransition::getProb(){
  return this->probability;
}

void ProbTransition::setTrigger(char c) {
  this -> trigger = c;
}

bool ProbTransition::isTrigger(char c) {
  return this -> trigger == c;
}

char ProbTransition::getTrigger() {
  return this -> trigger;
}