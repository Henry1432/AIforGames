local Boids = { _version = "0.1.0" }

local Agent = require("agent")
local vector = require("vector")

Boids.all = {}

function Boids.init(count)
  for i = 1, count do
    table.insert(Boids.all, Agent.new())
  end
end

local alignment_force = function(neighbors, self)
  -- body
end

local separation_force = function(neighbors, self)
  -- body
end

local cohesion_force = function(neighbors, self)
  -- body
end

-- updates a single boid:
local update_boid = function(dt, neighbors, self)
  -- physics and stuff

  -- update:
  self:update(dt)
end

function Boids.update(dt)
  for i, agent in ipairs(Boids.all) do
    -- get local flock:
    local neighbors = {}
    for j, other in ipairs(Boids.all) do
      if i ~= j then
        local dist = vector.distance(agent.position, other.position)
        if 30 >= dist  then
          table.insert(neighbors, other)
        end
      end
    end

    -- keeps the codebase clean:
    update_boid(dt, neighbors, agent)
  end
end

function Boids.draw()
	for _, agent in ipairs(Boids.all) do
		agent:draw()
	end
end

return Boids