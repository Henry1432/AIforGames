local Vec2 = require("utils.vector")

local Pheromone = {}
Pheromone.__index = Pheromone

--no need for force, code in monster

function Pheromone.new(world, position)
    local self = setmetatable({}, Pheromone)
    self.world = world
    self.position = Vec2(position.x, position.y)
	self.radius = 3
	
	world.shash:add(self, self.position.x, self.position.y, self.radius*2, self.radius*2)
    return self
end

function Pheromone:update(dt)

end

function Pheromone:draw()
    love.graphics.setColor(0.2, 0.3, 0.9)
    love.graphics.circle("fill", self.position.x, self.position.y, self.radius)

end



return Pheromone