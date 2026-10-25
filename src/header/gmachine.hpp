#include "heap.hpp"
#include "gcode.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class GMachine
{
    public:
        void execute(const gcode& code);
        void addGlobal(const std::string& name, int arity, std::size_t codeAd);
        void printStack() const;
        void printHeap() const;

    private:
        Heap heap;
        std::vector<Ad> stack;
        std::unordered_map<std::string, Ad> globals;
};