local Grid = {}
Grid.__index = Grid

function Grid.new(width, height)
  local self = setmetatable({}, Grid)
  self.width = width
  self.height = height

  -- matrix
  self.mt = {}
  for i = 1, self.height do
  	for j = 1, self.width do
  	  self.mt[(i + j * self.width) + 1] = 0
  	end
  end

  return self
end

function Grid:get(x, y)
  return self.mt[(x + y * self.width) + 1]
end

function Grid:set(x, y, value)
  self.mt[(x + y * self.width) + 1] = value
end

return Grid