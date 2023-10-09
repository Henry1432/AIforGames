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
        w->SetNodeColor(p, Color::Black);
        visited[0][0] = true;
        stack.push_back(p);
        return true;
    }
    auto index = Random::Range(0, 3);
    Point2D p;
    bool run = true;
    while (run)
    {
        switch (index) {
            case 0:
                p = stack[0].Up();
                if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2)
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                else if (visited[p.x][p.y]) 
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                visited[p.x][p.y] = true;
                w->SetNodeColor(p, Color::Black);
                stack[0] = p;
                run = false;
                break;
            case 1:
                p = stack[0].Right();
                if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2)
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                else if (visited[p.x][p.y]) 
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                visited[p.x][p.y] = true;
                w->SetNodeColor(p, Color::Black);
                stack[0] = p;
                run = false;
                break;
            case 2:
                p = stack[0].Down();
                if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2)
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                else if (visited[p.x][p.y]) 
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                visited[p.x][p.y] = true;
                w->SetNodeColor(p, Color::Black);
                stack[0] = p;
                run = false;
                break;
            case 3:
                p = stack[0].Left();
                if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2)
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                else if (visited[p.x][p.y]) 
                {
                    index = index > 0 ? ((index - 1) % 4) : 3;
                    break;
                }
                visited[p.x][p.y] = true;
                w->SetNodeColor(p, Color::Black);
                stack[0] = p;
                run = false;
                break;
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
  std::vector<Point2D> visitables;

  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  return neighbors;
}