local queue = require("utils.queue")
local vec = require("utils.vector")

-- FIXME: implement breadth first searh
return function(grid, x, y)
  local frontier = queue.new()
  frontier:push(vec(x, y))
  local came_from = {}
  came_from[grid:index_of(x, y)] = nil
  
  --logic
  while not frontier:empty() do
	local cur = frontier:pop()
	local neighbors = grid:get_neighbors(cur.x, cur.y)
	for i, n in ipairs(neighbors) do
		local index = grid:index_of(n.x, n.y)
		local valid = grid:get(n.x, n.y) == false
		local not_seen = came_from[index] == nil
		if valid and not_seen then
			frontier:push(vec(n.x, n.y))
			came_from[index] = cur
		end
	end
  end
  
  
  return came_from
end