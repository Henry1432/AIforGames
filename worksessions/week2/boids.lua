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

local tilemap_avoidence_force = function(neighbors, self)
	local tx = math.floor((self.position.x + self.velocity.x) / tile_width)
	local ty = math.floor((self.position.y + self.velocity.y) / tile_height)
	local px = math.floor((self.position.x) / tile_width)
	local py = math.floor((self.position.y) / tile_height)
	
	local force = vector(0,0)
	
	local velIsOnTile =  tilemap:get(tx, ty)
	
	if velIsOnTile == 1 then
		local up = false
		local down = false
		local right = false
		local left = false
		
		if py < ty then
			up = true
		elseif py >  ty then
			down = true
		end
		
		
		if px > tx then
			right = true
		elseif px < tx then
			left = true
		end
		
		
		local dif = 75
		if (up and not down) then
			if (not left and not right) then
				if not (tilemap:get((tx + dif), ty) == 1) then
					force.x = force.x + dif
				else
					force.x = force.x - dif
				end
			elseif (left and not right) then
				if not (tilemap:get((tx + dif), (ty - dif)) == 1) then
					force.x = force.x + dif
					force.y = force.y - dif
				elseif not (tilemap:get((tx - dif), (ty + dif)) == 1) then
					force.x = force.x - dif
					force.y = force.y + dif
				end
			elseif (right and not left) then
				if not (tilemap:get((tx + dif), (ty + dif)) == 1) then
					force.x = force.x + dif
					force.y = force.y + dif
				elseif not (tilemap:get((tx - dif), (ty - dif)) == 1) then
					force.x = force.x - dif
					force.y = force.y - dif
				end
			end
		elseif (down and not up) then
			if (not left and not right) then
				if not (tilemap:get((tx + dif), ty) == 1) then
					force.x = force.x + dif
				else
					force.x = force.x - dif
				end
			elseif (left and not right) then
				if not (tilemap:get((tx + dif), (ty + dif)) == 1) then
					force.x = force.x + dif
					force.y = force.y + dif
				elseif not (tilemap:get((tx - dif), (ty - dif)) == 1) then
					force.x = force.x - dif
					force.y = force.y - dif
				end
			elseif (right and not left) then
				if not (tilemap:get((tx + dif), (ty - dif)) == 1) then
					force.x = force.x + dif
					force.y = force.y - dif
				elseif not (tilemap:get((tx - dif), (ty + dif)) == 1) then
					force.x = force.x - dif
					force.y = force.y + dif
				end
			end
		elseif(not up and not down) then
			if (left and not right) then
				if not (tilemap:get(tx, (ty + dif)) == 1) then
					force.y = force.y + dif
				else
					force.y = force.y - dif
				end
			elseif (right and not left) then
				if not (tilemap:get(tx, (ty + dif)) == 1) then
					force.y = force.y + dif
				else
					force.y = force.y - dif
				end
			end
		end
		
		if(tilemap:get(px, py) == 1) then
			self.velocity.x = self.velocity.x * -1
			self.velocity.y = self.velocity.y * -1 

		end
		
	end

	return force
end

-- updates a single boid:
local update_boid = function(dt, neighbors, self)
	local acceleration = vector(0,0)
	local avoidance = tilemap_avoidence_force(nil, self)
	acceleration:add(avoidance)
	
	self.velocity:add(acceleration * dt)
	local speed = self.velocity:magnitude()
	local direction =  self.velocity / speed
	self.velocity = direction * 15

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