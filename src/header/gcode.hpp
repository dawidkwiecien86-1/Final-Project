#include <string>

// enum with all possible g-code instruction operands
enum class Instruct
{
    PushInt,
    PushGlobal,
    Push,
    MkAp
};

// contains the differents parts of a g-code instruction
struct gcode
{
    Instruct instruct;
    int operand = 0;
    std::string name = "";
};