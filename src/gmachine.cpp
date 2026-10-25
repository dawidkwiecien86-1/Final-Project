#pragma once
#include "gmachine.hpp"

#include <iostream>
#include <stdexcept>
#include <variant>
#include <type_traits>

void GMachine::addGlobal(const std::string& name, int arity, std::size_t codeAd)
{
    Ad ad = heap.allocate(globsk{arity, codeAd});
    globals[name] = ad;
}

void GMachine::execute(const gcode& code)
{
    switch (code.instruct)
    {
        case Instruct::PushInt:
        {
            Ad ad = heap.allocate(numNode{code.operand});
            stack.push_back(ad);
            break;
        }

        case Instruct::PushGlobal:
        {
            Ad ad = globals.at(code.name);
            stack.push_back(ad);
            break;
        }

        case Instruct::Push:
        {
            std::size_t offset = static_cast<std::size_t>(code.operand);

            if (code.operand < 0 || offset >= stack.size())
            {
                throw std::runtime_error("Invalid stack offset");
            }

            Ad ad = stack[(stack.size()-1) - offset];
            stack.push_back(ad);
            break;
        }

        case Instruct::MkAp:
        {
            if (stack.size() < 2)
            {
                throw std::runtime_error("'MKAP' requires at least two elements in the stack.");
            }

            Ad func = stack.back();
            stack.pop_back();

            Ad arg = stack.back();
            stack.pop_back();

            Ad app = heap.allocate(appNode{func, arg});
            stack.push_back(app);
            break;
        }
    }
}

void GMachine::printStack() const
{
    std::cout << "Stack (ascending): ";

    for (Ad ad : stack)
    {
        std::cout << ad << " ";
    }
    std::cout << "\n";
}

void GMachine::printHeap() const 
{
    std::cout << "Heap:" << "\n";

    for (Ad i = 0; i < heap.size(); ++i)
    {
        const Node& node = heap.get(i);
        std::cout << " " << i << ": ";

        std::visit([](const auto& value)
        {
            using Type = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<Type, numNode>)
            {
                std::cout << "NUM(" << value.val << ")";
            }
            else if constexpr (std::is_same_v<Type, appNode>) 
            {
                std::cout << "AP(" << value.func << ", " << value.arg << ")";
            }
            else if constexpr (std::is_same_v<Type, indNode>) 
            {
                std::cout << "IND(" << value.target << ")";
            }
            else if constexpr (std::is_same_v<Type, letrecNode>) 
            {
                std::cout << "LETREC";
            }
            else if constexpr (std::is_same_v<Type, globsk>) 
            {
                std::cout << "GLOBAL(arity=" << value.arity << ", code=" << value.codeAd << ")";
            }
        }, node);

        std::cout << "\n";
    }
}