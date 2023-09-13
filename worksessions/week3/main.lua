local Grid = require("grid")
local Boids = require("boids")

tilemap = nil

tile_width = 16
tile_height = 16


function love.load()
  tilemap = Grid.new(64, 64)
  Boids.init(5)
end

function love.update(dt)
  Boids.update(dt)
end

function love.mousepressed(x, y, button)
  local gx = math.floor(x / tile_width)
  local gy = math.floor(y / tile_height)
  if(tilemap:get(gx, gy) == 1) then
	tilemap:set(gx, gy, 0)
  else
	tilemap:set(gx, gy, 1)
  end
end

function love.draw()
  Boids.draw()

  -- tilemap
  for j = 0, tilemap.height - 1 do
    for i = 0, tilemap.width - 1 do
      local t = tilemap:get(i, j) == 1 and "fill" or "line"
      love.graphics.rectangle(t, i * tile_width, j * tile_height, tile_width, tile_height)
    end
  end

end