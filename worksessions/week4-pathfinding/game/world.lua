local World = {}
World.__index = World


local Shash = require("utils.shash-master.shash")
local shash = nil


function World.new(state)
    local self = setmetatable({}, World)
    self.search = {}
    self.monsters = {}
    self.ants = {}
    self.pList = {}
    self.hero = nil
    self.grid = nil
	
	self.shash = Shash.new(16)
	
    return self
end

-- function World:monsters()
--     return self.monsters
-- end

-- function World:hero()
--     return self.hero
-- end

-- function World:grid()
--     return self.grid
-- end

-- function World:search()
--     return self.search
-- end

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