#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

bool PrimExample::Step(World* w) {
  int sideOver2 = w->GetSize() / 2;

  if (!initialized) {
    Point2D p(0, 0);
    toBeVisited.push_back(p);
    w->SetNodeColor(p, Color::DarkRed);
    initialized = true;
    return false;
  }
  auto index = Random::Range(0, toBeVisited.size() - 1);
  auto nextPoint = toBeVisited[index];
  w->SetNodeColor(nextPoint, Color::Black);
  toBeVisited.erase(toBeVisited.begin() + index);

  // logic to be done
  auto visitables = getVisitables(w, nextPoint);

  //std::cout << "3:" << nextPoint.x << ", " << nextPoint.y << "|";
  std::cout << visitables.size() << "\n";
    //std::cout << "4:" << nextPoint.x << ", " << nextPoint.y << "|";
    for (int i = 0; i < visitables.size(); i++) {
      toBeVisited.push_back(visitables[i]);
      w->SetNodeColor(visitables[i], Color::DarkRed);
    }

    auto neighbors = getVisitedNeighbors(w, nextPoint);
    if (!neighbors.empty())
    {
      auto n = Random::Range(0, neighbors.size() - 1);
      auto dir = nextPoint - neighbors[n];
      auto parent = neighbors[n];

      /*if (dir.y  == 1)
      {
        w->SetNorth(point, false);
      }
      else if (dir.y  == -1)
      {
        w->SetSouth(point, false);
      } 
      else if (dir.x == -1) 
      {
        w->SetEast(point, false);
      }
      else if (dir.x == 1)
      {
        w->SetWest(point, false);
      }*/

    if (nextPoint == parent.Left()) 
    {
        w->SetEast(nextPoint, false);
    } 
    else if (nextPoint == parent.Down()) 
    {
        w->SetNorth(nextPoint, false);
    }
    else if (nextPoint == parent.Right()) 
    {
        w->SetWest(nextPoint, false);
    } 
    else if (nextPoint == parent.Up()) 
    {
        w->SetSouth(nextPoint, false);
    }
    }
  if (toBeVisited.size() == 0)
  {
    return false;
  }
  

  return true;
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;
    
  for (auto delta:deltas)
  {
    auto next = p + delta;
    if (abs(next.x) > sideOver2 || abs(next.y) > sideOver2) {
      continue;
    }
    if (w->GetNodeColor((next)) != Color::Black && w->GetNodeColor((next)) != Color::DarkRed) {
        visitables.push_back(next);
      }
  }
  

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;
  
  for (auto delta : deltas) {
    auto next = p + delta;
    if (abs(next.x) > sideOver2 || abs(next.y) > sideOver2) {
      continue;
    }
      if (w->GetNodeColor((next)) == Color::Black) {
        neighbors.push_back(next);
      }
  }

  return neighbors;
}
