#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
        // Try to avoid boids too close
        Vector2f separatingForce = Vector2f::zero();
        if (neighborhood.size() > 0) {
          float desiredDistance = desiredMinimalDistance;

          // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
          if (!neighborhood.empty()) {
            Vector2f position = boid->transform.position;
            int countCloseFlockmates = 0;
            // todo: find and apply force only on the closest mates
            Vector2f distance;
            int dotDist;
            for (int i = 0; i < neighborhood.size(); i++) {
              distance = position - neighborhood[i]->getPosition();
              dotDist = sqrt(distance.x * distance.x + distance.y * distance.y);
              if (dotDist < desiredDistance) 
              {
                countCloseFlockmates++;
                separatingForce += neighborhood[i]->getPosition();
              }
            }
            separatingForce = boid->getPosition() - (separatingForce / (countCloseFlockmates > 0 ? countCloseFlockmates : 1));

          }
        }

        separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
