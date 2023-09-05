local agents = {}

function love.load ()
	--try changing 200 to 1000
	--it looks like a boarder of red around the edge of the window
	for i = 1, 200 do
		table.insert (agents, 
		{
		--agent info
			x=64, y=64,
			radius = 8,
			vx = (math.random() * 2 - 1) * 150, vy = (math.random() * 2 - 1) * 150,
			crowded = false,
			proximity = 20,
			
			--target velocity, current velocity, acceleration, if target is under acceleration current = target
		})
	end
end

function love.update (dt)
	--screen wrapping and velocity
	local wWidth = love.graphics.getWidth()
	local wHeight = love.graphics.getHeight()
	for i, agent in ipairs (agents) do
		agent.x = agent.x + agent.vx * dt
		agent.y = agent.y + agent.vy * dt
		agent.x = agent.x % wWidth
		agent.y = agent.y % wHeight
		
		--crowded behavior
		local count = 0
		for j, agent2 in ipairs (agents) do
			if (agent2.x < agent.x + agent.proximity) then
				if (agent2.x > agent.x - agent.proximity) then
					if (agent2.y < agent.y + agent.proximity) then
						if (agent2.y > agent.y - agent.proximity) then
							count = count + 1
							if(agent2.x  > agent.x) then
								agent.vx = math.abs(agent.vx) * -1
							else
								agent.vx = math.abs(agent.vx)
							end
						
							if(agent2.y  > agent.y) then
								agent.vy = math.abs(agent.vy) * -1
							else
								agent.vy = math.abs(agent.vy)
							end
							
						end
					end
				end
			end
		end
		
		--draw red if true
		if (count > 4) then
			agent.crowded = true
		else
			agent.crowded = false
		end
	end

end

--drawing
function love.draw ()
	for i, agent in ipairs (agents) do
		if agent.crowded then
			love.graphics.setColor(1,0,0)
		else
			love.graphics.setColor(1,1,1)
		end
		love.graphics.circle( "fill", agent.x, agent.y, 10)
	end
end

-- :)