//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
#include <system_error>
#include <iostream>
void HexagonGameOfLife::Step(World& world) 
{
  for (auto y = 0; y < world.SideSize(); y++) {
    for (auto x = 0; x < world.SideSize(); x++) {
      auto currentPoint = Point2D(x, y);
      auto neighborCount = CountNeighbors(world, currentPoint);
      std::cout << neighborCount << "\n";

      if (world.Get(currentPoint)) {
        if (neighborCount <= 1) {
          world.SetNext(currentPoint, 0);
        } else if (neighborCount >= 3) {
          world.SetNext(currentPoint, 0);
        } else if (neighborCount == 2) {
          world.SetNext(currentPoint, 1);
        }
            
      } else {
        if (neighborCount == 2) {
          world.SetNext(currentPoint, 1);
        }
      }

      /*if (world.Get(currentPoint)) {
        if (neighborCount <= 1) {
          world.SetNext(currentPoint, 0);
        } else if (neighborCount >= 4) {
          world.SetNext(currentPoint, 0);
        } else if (neighborCount == 2 || neighborCount == 3) {
          world.SetNext(currentPoint, 1);
        }

      } else {
        if (neighborCount == 3) {
          world.SetNext(currentPoint, 1);
        }
      }*/
    }
  }

  world.SwapBuffers();
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  //count += world.Get(point.Up()) ? 1 : 0;
  //count += world.Get(point.Down()) ? 1 : 0;
  //count += world.Get(point.Left()) ? 1 : 0;
  //count += world.Get(point.Right()) ? 1 : 0;
  //count += world.Get(point.Up().Right()) ? 1 : 0;
  //count += world.Get(point.Up().Left()) ? 1 : 0;
  //count += world.Get(point.Down().Right()) ? 1 : 0;
  //count += world.Get(point.Down().Left()) ? 1 : 0;
  if ((point.y % 2) == 0)
  {
    count += world.Get(point.Left()) ? 1 : 0;
    count += world.Get(point.Right()) ? 1 : 0;
    count += world.Get(point.Up()) ? 1 : 0;
    count += world.Get(point.Up().Left()) ? 1 : 0;
    count += world.Get(point.Down()) ? 1 : 0;
    count += world.Get(point.Down().Left()) ? 1 : 0;
  }
  else
  {
    count += world.Get(point.Left()) ? 1 : 0;
    count += world.Get(point.Right()) ? 1 : 0;
    count += world.Get(point.Up()) ? 1 : 0;
    count += world.Get(point.Up().Right()) ? 1 : 0;
    count += world.Get(point.Down()) ? 1 : 0;
    count += world.Get(point.Down().Right()) ? 1 : 0;
  }


  return count;
}
