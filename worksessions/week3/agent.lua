local Agent = {}
Agent.__index = Agent

local vector = require("vector")

function Agent.new()
  local self = setmetatable({}, Agent)

  -- set random position:
  local w, h = love.graphics.getDimensions()
  local x = math.random() * w
  local y = math.random() * h

  -- set random direction:
  local dx = (math.random() * 2 - 1) * 15
  local dy = (math.random() * 2 - 1) * 15
  
  self.position = vector(x, y)
  self.acceleration = vector(0, 0)
  self.velocity = vector(dx, dy)
  self.angle = 0
  return self
end


function Agent:update(dt)
  -- add velocity to position; wrap screen:
  local w, h = love.graphics.getDimensions()
  self.position.x = (self.position.x + self.velocity.x * dt) % w
  self.position.y = (self.position.y + self.velocity.y * dt) % h
end

function Agent:draw()
  local x, y = math.floor(self.position.x), math.floor(self.position.y)

  -- body, head:
  love.graphics.setColor(1.0, 1.0, 1.0, 1.0)
  love.graphics.circle("fill", self.position.x, self.position.y, 4)
end

return Agent