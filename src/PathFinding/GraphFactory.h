#pragma once
#include "Graph.h"


class GraphFactory
{
public:
    GraphFactory(const int w, const int h, const int s) : width(w), height(h), sides(s) {}

    using Graph = PathFinding::Graph;
    using Node = PathFinding::Node;
    using NodeSet = PathFinding::Graph::NodeSet;

    Graph Generate() const;

    int width, height, sides;
};

