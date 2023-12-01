return function(x0, y0, x1, y1)
  local dx = math.abs(x1 - x0)
  local dy = -math.abs(y1 - y0)
  local sx = x0 < x1 and 1 or -1
  local sy = y0 < y1 and 1 or -1
  local err = dx + dy

  local plot = {}
  table.insert(plot, { x=x0, y=y0 })

  while x0 ~= x1 or y0 ~= y1 do
    if 2 * err - dy > dx - 2 * err then
      err = err + dy
      x0 = x0 + sx
    else
      err = err + dx
      y0 = y0 + sy
    end
    table.insert(plot, { x=x0, y=y0 })
  end
  return plot
end