////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
namespace xi {



//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

    int MultOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
    {
        if(op != '*')
            throw std::logic_error("Operation other than Multiplication (*) are not supported");

        // here we just ignore unused operands
        return a * b;
    }

    IOperation::Arity MultOp::getArity() const
    {
        return arDue;
    }

    int DivOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
    {
        if(op != '/')
            throw std::logic_error("Operation other than Division (/) are not supported");
        if (b == 0)
            return INT_MAX;

        // here we just ignore unused operands
        return a / b;
    }

    IOperation::Arity DivOp::getArity() const
    {
        return arDue;
    }

    int InverOp::operation(char op, int a, int /*b*/, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
    {
        if(op != '~')
            throw std::logic_error("Operation other than Inversion (~) are not supported");

        // here we just ignore unused operands
        return ~a;
    }

    IOperation::Arity InverOp::getArity() const
    {
        return arUno;
    }


//==============================================================================
// class StackMachine
//==============================================================================
void StackMachine::registerOperation(char symb, xi::IOperation *oper) {
        SymbolToOperMapConstIter iterator = _opers.find(symb);
        if(iterator != _opers.end())
            throw std::logic_error("An operation " + std::string(1, symb) + " is already registered...");
        _opers[symb] = oper;
}

IOperation* StackMachine::getOperation(char symb) {
    SymbolToOperMapConstIter iterator = _opers.find(symb);
    if (iterator != _opers.end())
        return iterator -> second;
    else
        return nullptr;
}

int StackMachine::calculate(const std::string &expr, bool clearStack) {
    int n = 0;
    if (expr.empty())
        throw std::logic_error("Empty string!");
    else
        n = expr.length();
    char* word = new char[n];          //Буфер для считывания строки

    std::stringstream x;        //Создание потоковой переменной
    x << expr;                //Перенос строки в поток

    std::vector<std::string> v1;

    while (x >> word) v1.push_back(word);

    for (int i = 0; i < v1.size(); i++){
        std::stringstream st(v1[i]);
        int t;
        if (st >> t)
            _s.push(t);
        else{
            if (getOperation(v1[i][0]) == nullptr)
                throw std::logic_error("An operation " + std::string(1, v1[i][0]) + " is not registered...");
            xi::IOperation *op = getOperation(v1[i][0]);
            if (op->getArity() == op->arUno){
                t = _s.pop();
                t = op->operation(v1[i][0], t);
                _s.push(t);
            }
            else{
                int b = _s.pop();
                int a = _s.pop();
                b = op->operation(v1[i][0], a, b);
                _s.push(b);
            }
        }
    }
    v1.clear();
    x.str("");
    delete[] word;
    return _s.top();
}

// TODO: put StackMachine methods implementation here


} // namespace xi
