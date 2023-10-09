#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat : public Agent {
public:
  explicit Cat() : Agent(){};
  Point2D Move(World*) override;
  void FindGoal(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world);
  void Reorient(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world);
  
  int CheckPath(std::map<int, std::map<int, PathTile>>& searched, Point2D pos, PathTile& moveTo, World* world);

  bool ifAdd(const PathTile& hold, std::vector<PathTile>& neighbors);
  void setValue(PathTile& hold, Point2D& neighbor, std::map<int, std::map<int, PathTile>>& searched, World* world);
  void setValue(PathTile& hold, Point2D& neighbor, std::map<int, std::map<int, PathTile>>& searched, World* world, bool fullpath);


private:
    PathTile goal;
    std::vector<PathTile> runningPath;
    std::vector<PathTile> fullPath;

    
    const int PATH_PENALTY = 3;
};

#endif  // CAT_H
