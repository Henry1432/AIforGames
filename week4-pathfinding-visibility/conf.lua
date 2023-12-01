local tile_size = 16
local width_in_tiles = 50
local height_in_tiles = 50

love.filesystem.setSymlinksEnabled(true)

G = {
  title = "Breadth First Search",
  width = width_in_tiles * tile_size,
  height = height_in_tiles * tile_size,
  scale = 1,
  debug = false,
}

function love.conf(t)
  t.window.title = G.title
  t.window.width = G.width * G.scale
  t.window.height = G.height * G.scale
  t.console = true
end