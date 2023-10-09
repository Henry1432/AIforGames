#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"

#include <map>
#include <vector>
#include <sstream>
#include <iostream>

struct PathTile {
    // higher is worse
    int value = -1;

    Point2D lastTile;
    Point2D pos;
    Point2D nextTile;

    void print() 
    {
        std::ostringstream sout;
        sout << "pos: " << pos.x << ", " << pos.y << std::endl;
        sout << "\tlastTile: " << lastTile.x << ", " << lastTile.y << std::endl;
        sout << "\nextTile: " << nextTile.x << ", " << nextTile.y << std::endl;
        sout << "\tvalue: " << value << std::endl;
        std::cout << sout.str();
    }

    operator int() const
    {
        return value;
    }

    bool operator==(const PathTile& tile)
    {
        if (value == tile.value && lastTile == tile.lastTile && pos == tile.pos && nextTile == tile.nextTile)
        {
            return true;
        }
        return false;
    }
};

class World;

class Agent {
public:
  explicit Agent() = default;
  ;
  virtual Point2D Move(World*) = 0;
};

#endif  // AGENT_H
