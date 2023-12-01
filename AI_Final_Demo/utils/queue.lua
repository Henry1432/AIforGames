local queue = {}
queue.__index = queue

function queue.new()
  local self = setmetatable({}, queue)
  self._list = {
    first = 0,
    last = -1,
  }
  return self
end

function queue:push(value)
  local last = self._list.last + 1
  self._list.last = last
  self._list[last] = value
end

function queue:pop()
  if self:empty() then
    error("queue is empty")
  end
  local first = self._list.first
  local value = self._list[first]
  self._list[first] = nil
  self._list.first = first + 1
  return value
end

function queue:empty()
  return self._list.first > self._list.last
end

return queue