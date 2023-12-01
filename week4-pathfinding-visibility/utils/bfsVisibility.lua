local queue = require("utils.queue")
local vec = require("utils.vector")
local bresenham = require("utils.bresenham")

--local has_line_of_sight = function(grid, plot)
--    for i, v in ipairs(plot) do
--        if grid:get((v.x), (v.y)) then
--            return false;
--        end
--    end
--    
--    return true
--end

--look through the path:
	--if any are walls count how far away the tile is from that wall
	--failing that return -1
local set_Visibility = function(grid, plot)
	local count = -1
	local startCount = false;
	for i, v in ipairs(plot) do
        if grid:get((v.x), (v.y)) then
            startCount = true
			count = 0
        end
		if(startCount) then
			count = count + 1
		end
    end
    
    return count
end

return function(grid, x, y)
	--setup
	local frontier = queue.new()
	frontier:push(vec(x, y))
	local came_from_value = {}
	came_from_value[grid:index_of(x, y)] = nil
  
  --turn this into visibility grid
  --logic
  while not frontier:empty() do
	local cur = frontier:pop()
	local neighbors = grid:get_neighbors(cur.x, cur.y)
	for i, n in ipairs(neighbors) do
		local index = grid:index_of(n.x, n.y)
		local valid = grid:get(n.x, n.y) == false
		local not_seen = came_from_value[index] == nil
		
		if valid and not_seen then
			local plot = bresenham(x,y, n.x, n.y)
			
			local distance = set_Visibility(grid, plot)
			frontier:push(vec(n.x, n.y))
			came_from_value[index] = distance
		end
	end
  end
  
  
  return came_from_value
end