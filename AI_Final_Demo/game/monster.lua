local Vec2 = require("utils.vector")
local BFSH = require("utils.bfsHide")

local Monster = {}
Monster.__index = Monster

local pathfinding_force = function(self)
	--groundwork
	local force = Vec2(0, 0)
	
	local x = math.floor(self.position.x / 16)
	local y = math.floor(self.position.y / 16)
	
	--check bfsHide for next move
	local curTile = self.world.grid:index_of(x, y)
	local nextTile = BFSH(self.world.grid, self.world.visibility, x, y, 5)
	
	
	if nextTile ~= nil then
		local worldSpaceTile = Vec2(nextTile.x+0.5, nextTile.y+0.5) * 16
		local direction = (worldSpaceTile - self.position):normalize()
		
		force = direction
	end
	
	return force
end

--load in monster
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
	self.heading = pathfinding_force(self)
	self.heading:normalize()
	
	-- actual moving!
	self.position.x = self.position.x + (self.heading.x * 25 * dt)
	self.position.y = self.position.y + (self.heading.y * 25 * dt)
end

function Monster:draw()
	love.graphics.setColor(1.0, 1.0, 1.0)
	love.graphics.circle("fill", self.position.x, self.position.y, 8)
	
	love.graphics.setColor(1.0, 0.0, 0.0)
	love.graphics.line(self.position.x, self.position.y, self.position.x + self.heading.x * 15, self.position.y + self.heading.y * 15)
end

return Monster