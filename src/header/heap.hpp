#include <cstddef>
#include <stdexcept>
#include <utility>
#include <variant>
#include <vector>

// Definition of the memory address
using Ad = std::size_t;

// A simple node that just contains a single number
struct numNode 
{
    int val;
};

// contains links to a function as well as its argument
struct appNode 
{
    Ad func;
    Ad arg;
};

// contains a pointer to the node it is indirectional to
struct indNode 
{
    Ad target;
};

// node will be used for recursive letrec definitions
struct letrecNode {};

// defines a supercombinator node
struct globsk 
{
    int arity;
    std::size_t codeAd;
};

// all the different node types we'll be dealing with
using Node = std::variant<numNode, appNode, indNode, letrecNode, globsk>;

class Heap
{
    public:
        Ad allocate(Node node);
        Node& get(Ad ad);
        const Node& get(Ad ad) const;
        void update(Ad ad, Node node);
        std::size_t size() const;

    private:
        std::vector<Node> nodes;
};