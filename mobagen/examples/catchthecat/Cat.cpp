#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();
    std::map<int, std::map<int, PathTile>> searched;
    //IDEA: record and play back games?
    
    //if goal is invalid find a new one from 0,0
    if (goal.value == -1)
    {
        fullPath.append_range(runningPath);
        runningPath.clear();
        FindGoal(searched, pos, world);
    }
    //find real path to goal
    Reorient(searched, pos, world);


    //go from goal and look back till the player, keeping track of value
    PathTile moveTo;
    moveTo.lastTile = goal.lastTile;
    moveTo.value = goal.value;
    moveTo.pos = goal.pos;
    
    int pathValue = CheckPath(searched, pos, moveTo, world);

    //Anxiaty: if the value is below  0 or above a certian point make the goal invalid
    if (pathValue > 35 || pathValue < 0)
    {
        goal.value = -1;
    }

    //add next move to running path
    runningPath.push_back(moveTo);
    if (moveTo.pos == goal.pos) {
      return goal.pos;
    }
    //return next move
    return moveTo.pos;
}

// initial/reset goal find
void Cat::FindGoal(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world) 
{
    //set up goal from 0,0
    searched.empty();
    PathTile start;
    start.pos = Point2D(0, 0);
    start.lastTile = Point2D(0, 0);
    start.value = 0;
    
    //set up loop
    std::vector<PathTile> neighbors;
    neighbors.push_back(start);
    
    bool loop = true;
    bool searching = true;

    while (loop)
    {
        //check neighbors of the top neighbor position to be valid
        for (Point2D neighbor : world->neighbors(neighbors[0].pos)) 
        {
            if(world->isValidPosition(neighbor))
            {
                if (!world->getContent(neighbor) && searched[neighbor.x][neighbor.y].value == -1)
                {
                    if (world->catWinsOnSpace(neighbor) && searching)
                    {
                        //if valid goal set to goal and stop searching
                        PathTile tempGoal;
                        tempGoal.pos = neighbor;
                        tempGoal.lastTile = neighbors[0].pos;
                        tempGoal.value = 0;
                        goal = tempGoal;
                        searching = false;
                    }
                    PathTile hold;
                    hold.pos = neighbor;
                    hold.lastTile = neighbors[0].pos;

                    //check if we need to add this neighbor
                    if (ifAdd(hold, neighbors) && searching)
                    {
                        hold.value = 0;

                        //set the value of the neighbor and add it to the list of neighbors
                        setValue(hold, neighbor, searched, world, true);
                        neighbors.push_back(hold);
                    }
                }
            }
        }

        //if the goal is found set it
        if (goal.value != -1)
        {
            searched[goal.pos.x][goal.pos.y].value = goal.value;
            searched[goal.pos.x][goal.pos.y].nextTile = goal.nextTile;
            searched[goal.pos.x][goal.pos.y].pos = goal.pos;
            searched[goal.pos.x][goal.pos.y].lastTile = goal.lastTile;
        }
        //set active tile on searched map and erase it from neighbors
        searched[neighbors[0].pos.x][neighbors[0].pos.y].value = neighbors[0].value;
        searched[neighbors[0].pos.x][neighbors[0].pos.y].nextTile = neighbors[0].nextTile;
        searched[neighbors[0].pos.x][neighbors[0].pos.y].pos = neighbors[0].pos;
        searched[neighbors[0].pos.x][neighbors[0].pos.y].lastTile = neighbors[0].lastTile;
        neighbors.erase(neighbors.begin());

        //if there are no more neighbors and the goal is found break
        if (goal.value != -1 && neighbors.size() == 0)
        {
            loop = false;
        }

        // sort the neighbors by value so we persue the best tiles first
        std::sort(neighbors.begin(), neighbors.end());
    }
}
void Cat::Reorient(std::map<int, std::map<int, PathTile>>& searched, const Point2D pos, World* world) {
    //reorent, look for the set goal and find the path there

    //setup
    searched.clear();
    PathTile start;
    start.pos = Point2D(pos);
    start.lastTile = Point2D(pos.x+1, pos.y+1);
    start.value = 0;

    std::vector<PathTile> neighbors;
    neighbors.push_back(start);

    bool loop = true;
    bool searching = true;

    while (loop) {
        {
            for (Point2D neighbor : world->neighbors(neighbors[0].pos)) {
                if (world->isValidPosition(neighbor)) {
                    if (!world->getContent(neighbor) && searched[neighbor.x][neighbor.y].value == -1) {
                        //if the tile is valid
                        if (neighbor == goal.pos && searching) {
                            //if it is the goal we found in FindGoal stop searching
                            PathTile tempGoal;
                            tempGoal.pos = neighbor;
                            tempGoal.lastTile = neighbors[0].pos;
                            tempGoal.value = 0;
                            goal = tempGoal;
                            searching = false;
                        }
                        PathTile hold;
                        hold.pos = neighbor;
                        hold.lastTile = neighbors[0].pos;

                        //if the tile should be added set the value and add it
                        if (ifAdd(hold, neighbors) && searching) 
                        {
                            hold.value = 0;

                            setValue(hold, neighbor, searched, world);
                            neighbors.push_back(hold);
                        }
                    }
                }
            }

            //if the goal is found set it 
            if (goal.value != -1 && !searching) {
                searched[goal.pos.x][goal.pos.y].value = goal.value;
                searched[goal.pos.x][goal.pos.y].nextTile = goal.nextTile;
                searched[goal.pos.x][goal.pos.y].pos = goal.pos;
                searched[goal.pos.x][goal.pos.y].lastTile = goal.lastTile;
            }
            //add the active tile to the searched map
            searched[neighbors[0].pos.x][neighbors[0].pos.y].value = neighbors[0].value;
            searched[neighbors[0].pos.x][neighbors[0].pos.y].nextTile = neighbors[0].nextTile;
            searched[neighbors[0].pos.x][neighbors[0].pos.y].pos = neighbors[0].pos;
            searched[neighbors[0].pos.x][neighbors[0].pos.y].lastTile = neighbors[0].lastTile;
            //remove active tile from list of neighbors
            neighbors.erase(neighbors.begin());

            //if the goal is found and there are no more neighbors to check break loop
            if (!searching && goal.value != -1 && neighbors.size() == 0) {
                loop = false;
            }
            //sort the neighbors by value so we persue the best tiles first
            std::sort(neighbors.begin(), neighbors.end());
        }
    }
}

bool Cat::ifAdd(const PathTile& hold, std::vector<PathTile>& neighbors)
{
    //unless we already know about the tile return false
    bool add = true;
    for (PathTile count : neighbors) {
        if (count.pos == hold.pos) {
            add = false;
        }
    }
    return add;
}

void Cat::setValue(PathTile& hold, Point2D& neighbor, std::map<int, std::map<int, PathTile>>& searched, World* world) 
{
    //check the neighbors of the current tile 
    for (Point2D out : world->neighbors(neighbor)) 
    {
        if (world->isValidPosition(out))
        {
            //if they are valid make walls and tiles we have been to worse
            if (world->getContent(out)) 
            {
                hold.value = hold + 1;
            }

            if (searched[out.x][out.y] >= 0) 
            {
                for (PathTile run : runningPath) 
                {
                    if (run.pos == hold.pos) 
                    {
                        hold.value += PATH_PENALTY;
                    }
                }
            }
        }
    }
    //if the goal is set make the tiles that are closer to the goal better
    if (goal.value != -1)
    {
        int dist = std::sqrt(std::pow(hold.pos.x - goal.pos.x, 2) + std::pow(hold.pos.y - goal.pos.y, 2));
        hold.value += dist;
    }
}
void Cat::setValue(PathTile& hold, Point2D& neighbor, std::map<int, std::map<int, PathTile>>& searched, World* world, bool fullpath) {
    //same logic as above but if fullpath is specified also punish fullpath tiles
    
    for (Point2D out : world->neighbors(neighbor)) {
        if (world->isValidPosition(out)) {
            if (world->getContent(out)) {
                hold.value = hold + 1;
            }

            if (searched[out.x][out.y] >= 0) {
                for (PathTile run : runningPath) {
                    if (run.pos == hold.pos) {
                        hold.value += PATH_PENALTY;
                    }
                }
                if (fullpath)
                {
                    for (PathTile full : fullPath) {
                        if (full.pos == hold.pos) {
                            hold.value += PATH_PENALTY/2;
                        }
                    }
                }
            }
        }
    }
    if (goal.value != -1) {
        int dist = std::sqrt(std::pow(hold.pos.x - goal.pos.x, 2) + std::pow(hold.pos.y - goal.pos.y, 2));
        hold.value += dist;
    }
}

int Cat::CheckPath(std::map<int, std::map<int, PathTile>>& searched, Point2D pos, PathTile& moveTo, World* world) {
    int pathValue = 0;

    //check the safety of the current path
    for (PathTile step : runningPath)
    {
        for (Point2D neighbor : world->neighbors(step.pos))
        {
            if (world->getContent(neighbor))
            {
                pathValue++;
            }
        }
    }

    //also look at the path ahead and decide the next move
    while (moveTo.lastTile != pos) {
        moveTo.pos = moveTo.lastTile;
        moveTo.lastTile = searched[moveTo.pos.x][moveTo.pos.y].lastTile;
        moveTo.value = searched[moveTo.pos.x][moveTo.pos.y].value;

        if (moveTo.value < 0)
        {
            moveTo.value = 0;
        }
        pathValue += moveTo.value / 2;

        if (moveTo.pos == moveTo.lastTile)
        {
            break;
        }
    }

    //returning the predicted value of the full path
    std::cout << "PathValue: " << pathValue << std::endl;
    return pathValue;
}