local Vec2 = require("utils.vector")
local Pheromone = require("game.pheromone")

local Ant = {}
Ant.__index = Ant
local setBored = 2
local bored = setBored
local size = nil
local pGlobalTimer = 2


--no need for force, code in monster

function Ant.new(world)
    local self = setmetatable({}, Ant)
	size = Vec2(world.grid.w * 16, world.grid.h * 16)
    self.world = world
	self.pTimer = pGlobalTimer
    -- get a random tile:
    self.position = Vec2(size.x/2, size.y/2)
	local hx = (math.random() * 2 - 1)
	local hy = (math.random() * 2 - 1)
    self.heading = Vec2(hx, hy):normalize()

    return self
end

function Ant:update(dt)
	self.pTimer = self.pTimer - dt
	
	if self.pTimer <= 0 then
		self.pTimer = pGlobalTimer
		local p = Pheromone.new(self.world, self.position)
		table.insert(self.world.pList, p)
	end
	
	
	
	
	--world.shash:each(self.position.x + (self.heading.x * 2), self.position.y + (self.heading.y * 2), 6, 6, self:orient(self.heading, ))
	
	-- implementation
	--local force = 0
	--local x = 0
	--local y = 0
	--local w = 0
	--local h = 0 
	--world.shash:each(x, y, w, h, function(pheromones)
	--  local angle = self.positionm - pheremones.position
	--end)
	-- end implement
	
    --wander!
	bored = bored - dt
	if bored <= 0 then
		local hx = (math.random() - 0.5)
		local hy = (math.random() - 0.5)
		self.heading = Vec2(self.heading.x + hx, self.heading.y+ hy):normalize()
		bored = setBored
	end
	
    self.position.x = self.position.x + (self.heading.x * 15 * dt)
    self.position.y = self.position.y + (self.heading.y * 15 * dt)
	
	if (self.position.x < 0) or (self.position.x > size.x) then
		self.heading.x = -self.heading.x
	end
	if (self.position.y < 0) or (self.position.y > size.y) then
		self.heading.y = -self.heading.y
	end
end

--my guess is that you use the each in shash to run the reorienting code, make heading face the p and reset the random bored timer


function Ant:draw()
    love.graphics.setColor(0.0, 0.0, 0.0)
    love.graphics.circle("fill", self.position.x, self.position.y, 6)
	
	
    love.graphics.setColor(0.0, 1.0, 0.0)
	local newHeadingX = self.heading.x
	local newHeadingY = self.heading.y
	local angle = math.atan(self.heading.y / self.heading.x) * (180/3.1415)
	
	--use angle to make new heading
	
	love.graphics.circle("fill", self.position.x + newHeadingX * 200, self.position.y + newHeadingY * 200, 12)

    love.graphics.setColor(1.0, 0.0, 0.0)
    love.graphics.line(self.position.x, self.position.y, self.position.x + self.heading.x * 15, self.position.y + self.heading.y * 15)
end


return Ant