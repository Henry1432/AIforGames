#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f total;
  if (neighborhood.size() > 0) {
    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood

    for (int i = 0; i < neighborhood.size(); i++) {
      total += neighborhood[i]->getPosition();
    }
    total.x = total.x / neighborhood.size();
    total.y = total.y / neighborhood.size();

    cohesionForce = total - boid->getPosition();
  }
  // find center of mass

  return cohesionForce/2;
}