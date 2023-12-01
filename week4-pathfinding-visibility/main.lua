local Grid = require("utils.grid")
local BFSV = require("utils.bfsVisibility")

local Monster = require("game.monster")
local monster_count = 4

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

--get shadow color for draw step
local getShadowColor = function(v)
	local color = {1, 1, 1, 0}
		if(v ==-1) then
			color = {0.1, 0.1, 0.1, 0}
		elseif(v < 5) then
			color = {0.1, 0.1, 0.1, 0.9}
		elseif(v < 10) then
			color = { 0.2, 0.2, 0.2, 0.85}
		elseif(v < 15)then
			color = { 0.3, 0.3, 0.3, 0.8}
		elseif(v < 20)then
			color = { 0.4, 0.4, 0.4, 0.75}
		elseif(v < 25)then
			color = { 0.5, 0.5, 0.5, 0.7}
		elseif(v < 30)then
			color = { 0.6, 0.6, 0.6, 0.5}
		elseif(v < 35)then
			color = { 0.7, 0.7, 0.7, 0.3}
		elseif(v < 40)then
			color = { 0.8, 0.8, 0.8, 0.2}
		elseif(v >= 40) then
			color = { 0.9, 0.9, 0.9, 0.0}
		end
		
	return color
end


--load in world
function love.load()
	world = World.new()
	
	local w, h = love.graphics.getDimensions()
	world.grid = Grid.new(50, 50)
	
	for i = 0, monster_count do
		table.insert(world.monsters, Monster.new(world))
	end
end

function love.update(dt)
	--groundwork
	local mx, my = love.mouse.getPosition()
	mx = math.floor(mx / 16)
	my = math.floor(my / 16)
	
	world.visibility = BFSV(world.grid, mx, my)
	
	--monsters check visibility map for closest hiding spot and go there
	for _, monster in ipairs(world.monsters) do
		monster:update(dt)
	end
end

function love.draw()
	-- clear screen:
	love.graphics.clear(0.78, 0.78, 0.78)
	-- draw visibility map:
	if world.visibility then
		love.graphics.setColor(1.0, 1.0, 1.0)
		for y = 0, (world.grid.h - 1) do
			for x = 0, (world.grid.w - 1) do      
				--if the given tile is on the visibility map get the shadow color and draw accordingly
				local i = world.grid:index_of(x, y)
				local v = world.visibility[i]
				if v then
					local color = getShadowColor(v)
					
					love.graphics.setColor(color)
					love.graphics.rectangle("fill", x * 16, y * 16, 16, 16)
				end
			end
		end
	end
	
	-- draw grid over vis map
	love.graphics.setColor(0.0, 0.0, 0.0)
	for y = 0, (world.grid.h - 1) do
		for x = 0, (world.grid.w - 1) do
			local t = world.grid:get(x, y) and "fill" or "line"
			love.graphics.rectangle(t, x * 16, y * 16, 16, 16)
		end
	end


	for _, monster in ipairs(world.monsters) do
		monster:draw()
	end

	-- draw cursor over all
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