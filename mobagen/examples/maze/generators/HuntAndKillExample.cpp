#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w) 
{
    int sideOver2 = w->GetSize() / 2;
    if (!visited[0][0])
    {
        Point2D p(0, 0);
        w->SetNodeColor(p, Color::DarkRed);
        visited[0][0] = true;
        stack.push_back(p);
        return true;
    }
    auto index = Random::Range(0, 3);
    Point2D p;
    bool run = true;
    int stuckCount = 0;
    Point2D save;
    Color32 saveColor;
    
    while (run)
    {
        if (stuckCount > 3)
        {
            run = false;
        }

        switch (index) {
            case 0:
                save = stack[0];
                saveColor = w->GetNodeColor(save);
                w->SetNodeColor(save, Color::Black);
                p = stack[0].Up();
                if (move(w, p, index, stuckCount, run))
                {
                    w->SetSouth(stack[0], false);
                }
                else
                {
                    w->SetNodeColor(save, saveColor);
                }
                break;                
            case 1:
                save = stack[0];
                saveColor = w->GetNodeColor(save);
                w->SetNodeColor(save, Color::Black);
                p = stack[0].Right();
                if (move(w, p, index, stuckCount, run))
                {
                    w->SetWest(stack[0], false);
                }
                else
                {
                    w->SetNodeColor(save, saveColor);
                }
                break;
            case 2:
                save = stack[0];
                saveColor = w->GetNodeColor(save);
                w->SetNodeColor(save, Color::Black);
                p = stack[0].Down();
                if (move(w, p, index, stuckCount, run))
                {
                    w->SetNorth(stack[0], false);
                }
                else
                {
                    w->SetNodeColor(save, saveColor);
                }
                break;
            case 3:
                save = stack[0];
                saveColor = w->GetNodeColor(save);
                w->SetNodeColor(save, Color::Black);
                p = stack[0].Left();
                if (move(w, p, index, stuckCount, run))
                {
                    w->SetEast(stack[0], false);
                }
                else
                {
                    w->SetNodeColor(save, saveColor);
                }
                break;
        }
    }  
    
    if (stuckCount > 3)
    {
        w->SetNodeColor(stack[0], Color::Black);
        for (int y = sideOver2 * -1; y <= sideOver2; y++)
        {
            for (int x = sideOver2 * -1; x <= sideOver2; x++)
            {
                //Point2D p(x, y);
                if (abs(x) > sideOver2 || abs(y) > sideOver2)
                {
                    continue;
                } 
                else if (visited[x][y] && getVisitables(w, Point2D(x, y)).size() >0)
                {
                    stack[0] = Point2D(x, y);
                    w->SetNodeColor(stack[0], Color::DarkRed);
                    x = sideOver2;
                    y = sideOver2;
                }
            }
        }
    }

    return true;
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;

  for (auto delta : deltas) {
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
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
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

bool HuntAndKillExample::move(World* w, Point2D& p, int& index, int& stuckCount, bool& run) 
{    
    int sideOver2 = w->GetSize() / 2;
    if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2) 
    {
        index = index > 0 ? ((index - 1) % 4) : 3;
        stuckCount++;
        return false;
    } 
    else if (visited[p.x][p.y])
    {
        index = index > 0 ? ((index - 1) % 4) : 3;
        stuckCount++;
        return false;
    }
    stuckCount = 0;
    visited[p.x][p.y] = true;
    w->SetNodeColor(p, Color::DarkRed);
    stack[0] = p;
    run = false;
    return true;
}