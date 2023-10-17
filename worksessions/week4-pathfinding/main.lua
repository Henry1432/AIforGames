local Grid = require("utils.grid")
local BFS = require("utils.bfs")

local Monster = require("game.monster")
local Ant = require("game.ant")
local monster_count = 1
local ant_count = 3

local World = require("game.world")
local world = nil

math.randomseed(os.time())

-- assets:
local assets = {
    cursor = love.graphics.newImage("assets/cursor.png"),
    arrow = {
        img = love.graphics.newImage("assets/arrows.png"),
        r = love.graphics.newQuad(0, 0, 16, 16, 64, 16),
        d = love.graphics.newQuad(16, 0, 16, 16, 64, 16),
        l = love.graphics.newQuad(32, 0, 16, 16, 64, 16),
        u = love.graphics.newQuad(48, 0, 16, 16, 64, 16),
    },
}

function love.load()
  world = World.new()
  
  local w, h = love.graphics.getDimensions()
  world.grid = Grid.new(50, 50)

  -- TODO: generate a cave
  --walls randomize, then loop through and use the dungeon generation in life
  --grid has get neighbors

  -- create all monsters
  --for i = 0, monster_count do
  --  table.insert(world.monsters, Monster.new(world))
  --end
  --swap to ants!
	for i = 0, ant_count do
		table.insert(world.ants, Ant.new(world))
	end
  -- create the hero
end

function love.update(dt)
    ---- get mouse in tile space
    --local mx, my = love.mouse.getPosition()
    --mx = math.floor(mx / 16)
    --my = math.floor(my / 16)
	--
    ---- pathfinding:
    ---- FIXME: implement breadth first search in `utils/bfs.lua`
    --world.search = BFS(world.grid, mx, my)
	--
    ---- update the hero
    ---- update the monsters:
	
	
    for _, ant in ipairs(world.ants) do
        ant:update(dt)
   end
end

function love.draw()
    -- clear screen:
    love.graphics.clear(0.78, 0.78, 0.78)

    -- draw grid:
    love.graphics.setColor(0.0, 0.0, 0.0)
    for y = 0, (world.grid.h - 1) do
        for x = 0, (world.grid.w - 1) do
            local t = world.grid:get(x, y) and "fill" or "line"
            love.graphics.rectangle(t, x * 16, y * 16, 16, 16)
        end
    end

    -- draw search:
    --if world.search then
    --    love.graphics.setColor(1.0, 1.0, 1.0)
    --    for y = 0, (world.grid.h - 1) do
    --        for x = 0, (world.grid.w - 1) do      
    --            local i = world.grid:index_of(x, y)
    --            local v = world.search[i]
    --            if v and (v.x ~= nil and v.y ~= nil) then
    --                local dx, dy = x - v.x, y - v.y
    --                if dx > 0 then
    --                    love.graphics.draw(assets.arrow.img, assets.arrow.l, x * 16, y * 16)
    --                elseif dx < 0 then
    --                    love.graphics.draw(assets.arrow.img, assets.arrow.r, x * 16, y * 16)
    --                elseif dy > 0 then
    --                    love.graphics.draw(assets.arrow.img, assets.arrow.u, x * 16, y * 16)
    --                elseif dy < 0 then
    --                    love.graphics.draw(assets.arrow.img, assets.arrow.d, x * 16, y * 16)
    --                end
    --            end
    --        end
    --    end
    --end
	
	    for _, p in ipairs(world.pList) do
        p:draw()
    end

    for _, ant in ipairs(world.ants) do
        ant:draw()
    end

    -- draw cursor:
    local mx, my = love.mouse.getPosition()
    mx = math.floor(mx / 16) * 16
    my = math.floor(my / 16) * 16
    love.graphics.setColor(1.0, 1.0, 1.0)
    love.graphics.draw(assets.cursor, mx, my)
end

function love.mousepressed(x, y, button, istouch, presses)
    x = math.floor(x / 16)
    y = math.floor(y / 16)

    local new_value = not world.grid:get(x, y)
    world.grid:set(x, y, new_value)
end