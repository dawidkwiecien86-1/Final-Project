#pragma once
#include "heap.hpp"

#include <utility>

Ad Heap::allocate(Node node)
{
    nodes.push_back(std::move(node));
    return nodes.size()-1;
}

Node& Heap::get(Ad ad)
{
    return nodes.at(ad);
}

const Node& Heap::get(Ad ad) const 
{
    return nodes.at(ad);
}

void Heap::update(Ad ad, Node node)
{
    nodes.at(ad) = std::move(node);
}

std::size_t Heap::size() const
{
    return nodes.size();
}