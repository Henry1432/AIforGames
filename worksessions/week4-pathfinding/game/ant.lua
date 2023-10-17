local Vec2 = require("utils.vector")
local Pheromone = require("game.pheromone")

local Ant = {}
Ant.__index = Ant
local setBored = 2
local bored = setBored
local size = nil
local pGlobalTimer = 3


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
		table.insert(self.world.pList, Pheromone.new(self.world, self.position))
	end

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

function Ant:draw()
    love.graphics.setColor(0.0, 0.0, 0.0)
    love.graphics.circle("fill", self.position.x, self.position.y, 6)

    love.graphics.setColor(1.0, 0.0, 0.0)
    love.graphics.line(self.position.x, self.position.y, self.position.x + self.heading.x * 15, self.position.y + self.heading.y * 15)
end



return Ant