#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) 
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
    if (stack.size() > 0) {
        auto index = Random::Range(0, 3);
        Point2D p;
        bool run = true;
        int stuckCount = 0;
        Point2D save;
        Color32 saveColor;
        while (run) {
          if (stuckCount > 3) {
            run = false;
          }

          switch (index) {
            case 0:
              save = stack[stack.size() - 1];
              saveColor = w->GetNodeColor(save);
              w->SetNodeColor(save, Color::DarkRed);
              p = stack[stack.size() - 1].Up();
              if (move(w, p, index, stuckCount, run)) {
                w->SetSouth(stack[stack.size() - 1], false);
              } else {
                w->SetNodeColor(save, saveColor);
              }
              break;
            case 1:
              save = stack[stack.size() - 1];
              saveColor = w->GetNodeColor(save);
              w->SetNodeColor(save, Color::DarkRed);
              p = stack[stack.size() - 1].Right();
              if (move(w, p, index, stuckCount, run)) {
                w->SetWest(stack[stack.size() - 1], false);
              } else {
                w->SetNodeColor(save, saveColor);
              }
              break;
            case 2:
              save = stack[stack.size() - 1];
              saveColor = w->GetNodeColor(save);
              w->SetNodeColor(save, Color::DarkRed);
              p = stack[stack.size() - 1].Down();
              if (move(w, p, index, stuckCount, run)) {
                w->SetNorth(stack[stack.size() - 1], false);
              } else {
                w->SetNodeColor(save, saveColor);
              }
              break;
            case 3:
              save = stack[stack.size() - 1];
              saveColor = w->GetNodeColor(save);
              w->SetNodeColor(save, Color::DarkRed);
              p = stack[stack.size() - 1].Left();
              if (move(w, p, index, stuckCount, run)) {
                w->SetEast(stack[stack.size() - 1], false);
              } else {
                w->SetNodeColor(save, saveColor);
              }
              break;
          }
        }

        if (stuckCount > 3) {
          w->SetNodeColor(stack[stack.size() - 1], Color::Black);
          stack.pop_back();
        }

        return true;
    }

    return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
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

bool RecursiveBacktrackerExample::move(World* w, Point2D& p, int& index, int& stuckCount, bool& run) {
  int sideOver2 = w->GetSize() / 2;
  if (abs(p.x) > sideOver2 || abs(p.y) > sideOver2) {
    index = index > 0 ? ((index - 1) % 4) : 3;
    stuckCount++;
    return false;
  } else if (visited[p.x][p.y]) {
    index = index > 0 ? ((index - 1) % 4) : 3;
    stuckCount++;
    return false;
  }
  stuckCount = 0;
  visited[p.x][p.y] = true;
  w->SetNodeColor(p, Color::DarkRed);
  stack.push_back(p);
  run = false;
  return true;
}