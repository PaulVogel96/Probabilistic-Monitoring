#include "State.hpp"
#include "ProbTransition.hpp"

template <class T> State<T>::State(String name, Verdict indicatedVerdict)
{
    this->name = name;
    this->indicatedVerdict = indicatedVerdict;
}

template <class T> String State<T>::getName()
{
    return this->name;
}

template <class T> Verdict State<T>::getIndicatedVerdict()
{
    return this->indicatedVerdict;
}

template <class T> void State<T>::addOutgoingTransition(T* t)
{
    this->outgoingTransitions.add(t);
};


template <class T> List<T*>& State<T>::getOutgoingTransitions()
{
    return this->outgoingTransitions;
};

template <class T> bool State<T>::removeOutgoingTransition(T* t)
{
    int numTransitions = this->outgoingTransitions.getSize();
    for (int i = 0; i < numTransitions; i++)
    {
        T* tr = outgoingTransitions[i];
        if (tr == t)
        {
            this->outgoingTransitions.remove(i);
            return true;
        }
    }
    return false;
};

template class State<ProbTransition>;