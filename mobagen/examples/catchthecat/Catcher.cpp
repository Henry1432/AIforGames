#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
    auto side = world->getWorldSideSize() / 2;
  
    auto catPos = world->getCat();
	std::map<int, std::map<int, PathTile>> searched;

    //predict cat goal
    FindGoal(searched, catPos, world);

    //path set up
    std::vector<PathTile> path;
    PathTile pathTile;
    pathTile.nextTile = goal.pos;
    pathTile.lastTile = searched[goal.lastTile.x][goal.lastTile.y].lastTile;
    pathTile.pos = goal.lastTile;
    for (Point2D out : world->neighbors(pathTile.pos)) 
    {
        if (world->getContent(out)) 
        {
            //likes friends
            pathTile.value--;
        }
    }

    path.push_back(pathTile);


    while (pathTile.lastTile != catPos) 
    {
        //init this path tile
        pathTile.nextTile = pathTile.pos;
        pathTile.pos = pathTile.lastTile;
        pathTile.lastTile = searched[pathTile.lastTile.x][pathTile.lastTile.y].lastTile;
        
        for (Point2D out : world->neighbors(pathTile.pos)) 
        {
            if (world->getContent(out)) 
            {
                //likes friends
                pathTile.value--;
            }
        }
        //liks close to the goal
        pathTile.value -= sqrt(abs(pow(goal.pos.x - pathTile.pos.x, 2) + pow(goal.pos.y - pathTile.pos.y, 2)));
        //likes close to the cat
        pathTile.value += sqrt(abs(pow(catPos.x - pathTile.pos.x, 2) + pow(catPos.y - pathTile.pos.y, 2)));

        //the desired effect is this, find the best neighbor close to the goal and not crouding the cat to trap it effectivly
        //I like that it doesn't let the cat out often but it doesnt do it quickly

        path.push_back(pathTile);

        //add neighbors of main path to the path
        for (Point2D neighbor : world->neighbors(pathTile.pos))
        {
            PathTile hold;
            hold.pos = neighbor;
            hold.lastTile = pathTile.pos;
            hold.value =+ world->neighbors(hold.pos).size();

            path.push_back(hold);
        }
    }

    //find the best spot to block and block it
    PathTile block = path[0];
    for (PathTile& pathTile : path)
    {
        if (block.value < pathTile.value)
        {
            block = pathTile;
        }
    }

    //return block position
    std::cout << "block: " << block.pos.x << ", " << block.pos.y << std::endl;
    return block.pos;
}

void Catcher::FindGoal(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world) {
    //find goal set up, starting at cat pos
    searched.empty();
    std::vector<Point2D> neighbors;
    neighbors.push_back(pos);
    searched[pos.x][pos.y].pos = pos;
    searched[pos.x][pos.y].value = 0;
    searched[pos.x][pos.y].lastTile = pos;
    std::vector<Point2D> tempNeighbors;

    //loop idea if the neighbor is valid and unsearched check add info to searched
    bool loop = true;
    while (loop) {
      Point2D current = neighbors[0];
      neighbors.erase(neighbors.begin());

      tempNeighbors = world->neighbors(current);
      for (int i = 0; i < tempNeighbors.size(); i++) {
            if (searched[tempNeighbors[i].x][tempNeighbors[i].y].value == -1 && tempNeighbors[i] != pos && !world->getContent(tempNeighbors[i])) {
              // is it a wall?
              if (!world->catWinsOnSpace(tempNeighbors[i])) {
                neighbors.push_back(tempNeighbors[i]);
                searched[tempNeighbors[i].x][tempNeighbors[i].y].lastTile = searched[current.x][current.y].pos;
                searched[tempNeighbors[i].x][tempNeighbors[i].y].value = searched[current.x][current.y].value + 1;
                searched[tempNeighbors[i].x][tempNeighbors[i].y].pos = tempNeighbors[i];
                // searched[tempNeighbors[i].x][tempNeighbors[i].y].print();
              } else if (world->catWinsOnSpace(tempNeighbors[i])) {
                  //if cat wins on space set goal and break loop
                neighbors.push_back(tempNeighbors[i]);
                searched[tempNeighbors[i].x][tempNeighbors[i].y].lastTile = searched[current.x][current.y].pos;
                searched[tempNeighbors[i].x][tempNeighbors[i].y].value = searched[current.x][current.y].value + 1;
                searched[tempNeighbors[i].x][tempNeighbors[i].y].pos = tempNeighbors[i];
                // searched[tempNeighbors[i].x][tempNeighbors[i].y].print();
                loop = false;

                goal.lastTile = searched[tempNeighbors[i].x][tempNeighbors[i].y].lastTile;
                goal.value = searched[tempNeighbors[i].x][tempNeighbors[i].y].value;
                goal.pos = searched[tempNeighbors[i].x][tempNeighbors[i].y].pos;
                break;
              }
            } else if (world->getContent(tempNeighbors[i])) {
              // std::cout << tempNeighbors[i].x << ", " << tempNeighbors[i].y << ": " << "Wall!\n";
            }
      }
    }
}