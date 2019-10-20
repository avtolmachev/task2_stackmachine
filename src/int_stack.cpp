////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include <stdexcept>
#include "int_stack.h"

// TODO: add necessary headers here
// #include <...

namespace xi {
    IntStack::IntStack(size_t sz){
        if (sz < 0 || sz > STACK_SIZE)
            throw std::logic_error("Invalid stack size!");
        _ssize = sz;
        _head = -1;
        _stack = new int[_ssize];
    }

    IntStack:: ~IntStack(){
        delete[] _stack;
    }

    void IntStack::push(int el) {
        if (isFull())
            throw std::logic_error("Stack is full");
        else{
            _head++;
            _stack[_head] = el;
        }

    }

    int IntStack::pop() {
        if (isEmpty())
            throw std::logic_error ("Stack is empty") ;
        else{
            int temp = _stack[_head];
            _stack[_head] = 0;
            _head--;
            return temp;
        }
    }
    int IntStack::top() {
        if (!isEmpty())
            return _stack[_head];
        else
            throw std::logic_error ("Stack is empty") ;
    }

    void IntStack::clear() {
        delete[] _stack;
        _stack = new int[_ssize];
        _head = -1;
    }

    bool IntStack::isEmpty() const {
        if (_head == -1)
            return true;
        else
            return false;
    }

    bool IntStack::isFull() const {
        if (_head + 1 == _ssize)
            return true;
        else
            return false;
    }
// TODO: add method definitions here

} // namespace xi

