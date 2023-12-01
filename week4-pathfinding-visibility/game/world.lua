local World = {}
World.__index = World

function World.new(state)
	local self = setmetatable({}, World)
	self.search = {}
	self.visibility = {}
	self.monsters = {}
	self.hero = nil
	self.grid = nil
	return self
end

function World:monsters()
     return self.monsters
 end

function World:random_spawn()
	local x, y = 0, 0
	while true do
		x = math.floor(math.random() * self.grid.w)
		y = math.floor(math.random() * self.grid.h)
		if not self.grid:get(x, y) then
			break
		end
	end
	
	return x, y
end


return World