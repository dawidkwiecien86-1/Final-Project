#pragma once
#include "gmachine.hpp"

#include <cassert>
#include <iostream>

int main()
{
    GMachine gm;

    gm.addGlobal("id", 1, 0);

    std::vector<gcode> program = 
    {
        {Instruct::PushInt, 86},
        {Instruct::PushGlobal, 0, "id"},
        {Instruct::MkAp}
    };

    for (const gcode& ginstruction : program)
    {
        gm.execute(ginstruction);
        gm.printStack();
    }

    gm.printHeap();

    return 0;
}