#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) 
{ 
    for (auto y = 0; y < world.SideSize(); y++)
    {
        for (auto x = 0; x < world.SideSize(); x++) 
        {
            auto currentPoint = Point2D(x, y);
            auto neighborCount = CountNeighbors(world, currentPoint);

            /*if (world.Get(currentPoint))
            {
                if (neighborCount <= 1) 
                {
                    world.SetNext(currentPoint, 0);
                } 
                else if (neighborCount >= 4)
                {
                    world.SetNext(currentPoint, 0);
                } 
                else if (neighborCount == 2 || neighborCount == 3)
                {
                    world.SetNext(currentPoint, 1);
                }

            }
            else
            {
                if (neighborCount == 3) 
                {
                    world.SetNext(currentPoint, 1);
                }
            }*/

            if (neighborCount > 4) {
              world.SetNext(currentPoint, 1);
            }
            if (neighborCount < 3) {
              world.SetNext(currentPoint, 0);
            }
                
        }
    }

    world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) 
{ 
	int count = 0;
	count += world.Get(point.Up()) ? 1 : 0; 
	count += world.Get(point.Down()) ? 1 : 0;
    count += world.Get(point.Left()) ? 1 : 0;
    count += world.Get(point.Right()) ? 1 : 0;
    count += world.Get(point.Up().Right()) ? 1 : 0;
    count += world.Get(point.Up().Left()) ? 1 : 0;
    count += world.Get(point.Down().Right()) ? 1 : 0;
    count += world.Get(point.Down().Left()) ? 1 : 0;

    return count;
}
