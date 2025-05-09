#include "State.hpp"
#include "Transition.hpp"


template<class T>
State<T>::State(String name){
    this->name = name;
}

template<class T>
bool State<T>::removeOutgoingTransition(T* t){
    int numTransitions = this -> outgoingTransitions.getSize();
    for(int i = 0; i < numTransitions; i++){
      T* tr = outgoingTransitions[i];
        if(tr == t) {
            this->outgoingTransitions.remove(i);
            return true;
        }
    }
    return false;
};


template<class T>
bool State<T>::deleteOutgoingTransition(T* t){
    int numTransitions = this -> outgoingTransitions.getSize();
    for(int i = 0; i < numTransitions; i++){
      T* tr = outgoingTransitions[i];
        if(tr == t) {
            this->outgoingTransitions.remove(i);
            delete &tr;
            return true;
        }
    }
    return false;
};

template<class T>
void State<T>::addOutgoingTransition(T* t){
    this->outgoingTransitions.add(t);
};

template<class T>
List<T*> State<T>::getOutgoingTransitions(){
    return this->outgoingTransitions;
};

template<class T>
String State<T>::toString(){
    return this->name;
}

//template class State<ProbTransition>;
template class State<Transition>;