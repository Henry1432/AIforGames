local grid = {}
grid.__index = grid

function grid.new(w, h, rand, prob)
	local self = setmetatable({}, grid)
	self.w = w
	self.h = h
	self.mt = {}
	for i = 1, self.w * self.h do
		self.mt[i] = false
	end
	return self
end

function grid:get_index(cx, cy)
	return 1 + cx + cy * self.w
end

function grid:index_of(x, y)
	return 1 + x + y * self.w
end

function grid:get(cx, cy)
	return self.mt[1 + cx + cy * self.w]
end

function grid:set(cx, cy, n)
	self.mt[1 + cx + cy * self.w] = n
end


function grid:get_by_index(index)
	return self.mt[index]
end

function grid:set_by_index(index, value)
	self.mt[index] = value
end


function grid:clear()
	for i = 1, self.w * self.h do
		self.mt[i] = 0
	end
end

function grid:in_bounds(cx, cy)
	if cx < 0 or cx >= self.w then return false end
	if cy < 0 or cy >= self.h then return false end
	return true
end

function grid:get_neighbors(cx, cy)
	local n = {
		{ x = cx + 1, y = cy },
		{ x = cx, y = cy - 1 },
		{ x = cx - 1, y = cy },
		{ x = cx, y = cy + 1 },
	}
	-- JUICE!
	if (cx + cy) % 2 == 0 then
		local i, j = 1, #n
		while i < j do
		n[i], n[j] = n[j], n[i]
		i = i + 1
		j = j - 1
		end
	end
	local ret = {}
	for _, v in ipairs(n) do
		if self:in_bounds(v.x, v.y) then
		table.insert(ret, v)
		end
	end
	return ret
end

function grid:collide(x, y, w, h)
	local left = math.floor(x / 16)
	local right = math.floor((x + w - 1) / 16)
	local top = math.floor(y / 16)
	local bottom = math.floor((y + h - 1) / 16)
	for i = left, right do
		for j = top, bottom do
		local t = self:get(i, j)
		if t ~= 0 then
			return true
		end
		end
	end
	return false
end

return grid