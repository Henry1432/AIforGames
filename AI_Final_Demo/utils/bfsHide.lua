local queue = require("utils.queue")
local vec = require("utils.vector")
local bresenham = require("utils.bresenham")

--very similar to bfsVisibility
return function(grid, visibility, x, y, margin)
	if(not grid:get(x, y)) then
		--setup
		local goal = vec(x, y)
		local frontier = queue.new()
		frontier:push(vec(x, y))
		local came_from = {}
		came_from[grid:index_of(x, y)] = nil
		
		--logic
		while not frontier:empty() and goal == vec(x, y) do
			local cur = frontier:pop()
			local neighbors = grid:get_neighbors(cur.x, cur.y)
			
			for i, n in ipairs(neighbors) do
				local index = grid:index_of(n.x, n.y)
				local valid = grid:get(n.x, n.y) == false
				local not_seen = came_from[index] == nil
				
				--add tile to came_from map, if not visible and within the given margin set as goal and bail
				if valid and not_seen then
					frontier:push(vec(n.x, n.y))
					came_from[index] = cur
					if(visibility[index]) then
						if (visibility[index] ~= -1 and visibility[index] < margin) then
								goal = vec(n.x, n.y)
						end
					end
				end
			end
		end
		
		--then trace back from goal to given position
		local nextTile = goal
		local searching = true
		while searching do
			local curIndex = grid:index_of(nextTile.x, nextTile.y)
			local traceTile = came_from[curIndex]
			if(traceTile ~= nil) then
				local selfTest = came_from[grid:index_of(traceTile.x, traceTile.y)]
				
				nextTile = traceTile
				if(selfTest == vec(x, y)) then
					searching = false
				end
			else
				searching = false
				nextTile = goal
			end
		end
		
		return nextTile
	end
end