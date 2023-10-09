#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"



class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
  void FindGoal(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world);

private:
  PathTile goal;
};

#endif  // CATCHER_H
