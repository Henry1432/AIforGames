local Vec2 = require("utils.vector")

local Monster = {}
Monster.__index = Monster

-- TODO: calculate a path
local pathfinding_force = function(self)
    local force = Vec2(0, 0)
	
	--where does the tile im on want to go?
	
	local x = math.floor(self.position.x / 16)
	local y = math.floor(self.position.y / 16)
	
	local curTile = self.world.grid:index_of(x, y)
	local nextTile = self.world.search[curTile]
	
	if nextTile ~= nil then
		local worldSpaceTile = Vec2(nextTile.x+0.5, nextTile.y+0.5) * 16
		local direction = (worldSpaceTile - self.position):normalize()
		
		--direction = (nextTile - Vec2(x,y)):normalize()
		
		force = direction
	end
	
    return force
end

local seperation_force = function(self, seperation_distance)
    local force = Vec2(0, 0)
	
	--where does the tile im on want to go?
	
	local x = math.floor(self.position.x / 16)
	local y = math.floor(self.position.y / 16)
	
	local sepCount = 0
	--if other boid is within distance add their relative position to force
	--tile based?
	for i, mon in ipairs(self.world.monsters) do
		if(mon.position ~= self.position) then
			local monDist = self.position - mon.position
			local dotDist = math.sqrt(monDist.x * monDist.x + monDist.y * monDist.y)
			if (dotDist < seperation_distance and dotDist ~= 0) then
				sepCount = sepCount+1
				force = force + monDist
			end
		end
	end
	
	if sepCount == 0 then
		sepCount = 1
	end
	force = (self.position - (force/sepCount)):normalize()
	
    return force
end

function Monster.new(world)
    local self = setmetatable({}, Monster)

    self.world = world

    -- get a random tile:
    local tx, ty = world:random_spawn()
    self.position = Vec2((tx * 16) - 8, (ty * 16) - 8)
    self.heading = Vec2(0, 0)

    return self
end

function Monster:update(dt)
    -- TODO: this should be a force being applied as acceleration
    self.heading = pathfinding_force(self)
	self.heading = self.heading + (seperation_force(self, 30) * 0.7)
	self.heading:normalize()

    -- TODO: implement other behaviors

    -- physics:
    self.position.x = self.position.x + (self.heading.x * 15 * dt)
    self.position.y = self.position.y + (self.heading.y * 15 * dt)
end

function Monster:draw()
    love.graphics.setColor(1.0, 1.0, 1.0)
    love.graphics.circle("fill", self.position.x, self.position.y, 8)

    love.graphics.setColor(1.0, 0.0, 0.0)
    love.graphics.line(self.position.x, self.position.y, self.position.x + self.heading.x * 15, self.position.y + self.heading.y * 15)
end

return Monster