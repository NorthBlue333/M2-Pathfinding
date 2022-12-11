#include "GraphFactory.h"

GraphFactory::Graph GraphFactory::Generate() const
{
    Graph g;

    NodeSet nodes;
    nodes.resize(width * height);


    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
        {
            nodes[y * width + x] = new Node{ x, y };
        }
    }

    //add children
    // for square
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const int index = y * width + x;
            Node* current_node = nodes.at(index);
            if (x < width - 1)
            {
                current_node->AddNeighbor(nodes.at(index + 1));
            }
            if (x > 0 && y < height - 1)
            {
                current_node->AddNeighbor(nodes.at(index + width - 1));
            }
            if (y < height - 1)
            {
                current_node->AddNeighbor(nodes.at(index + width));
            }
            if (y < height - 1 && x < width - 2)
            {
                current_node->AddNeighbor(nodes.at(index + width + 1));
            }
        }
    }

    // for hexagon
    /*
    for (int y = 0; y < height; y++)
    {
        const int offset = (y % 2);

        for (int x = 0; x < width; x++)
        {
            const int index = y * width + x;
            Node* current_node = nodes.at(index);

            if (x < width - 1)
            {
                current_node->AddNeighbor(nodes.at(index + 1));
            }
            if (x > 0 && y < height - 1)
            {
                current_node->AddNeighbor(nodes.at(index + width - 1 + offset));
            }
            if (y < height - 1 && x < width - 1 + offset)
            {
                current_node->AddNeighbor(nodes.at(index + width + offset));
            }
            if (y < height - 1 && x < width - 2 + offset)
            {
                current_node->AddNeighbor(nodes.at(index + width + 1 + offset));
            }
        }
    }
    */

    g.nodes = std::move(nodes);

    return g;
}
