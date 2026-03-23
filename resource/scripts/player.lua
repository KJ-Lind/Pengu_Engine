local Script = {}

function Script:onStart()
    print("Player script started")
end

function Script:onUpdate(dt)
    if IsKeyDown(Action.Arrow_Up) then
        local pos = self:getPosition()
        pos.z = pos.z - 0.005 * dt
        self:setPosition(pos)
    end
    if IsKeyDown(Action.Arrow_Down) then
        local pos = self:getPosition()
        pos.z = pos.z + 0.005 * dt
        self:setPosition(pos)
    end
    if IsKeyDown(Action.Arrow_Left) then
        local pos = self:getPosition()
        pos.x = pos.x - 0.005 * dt
        self:setPosition(pos)
    end
    if IsKeyDown(Action.Arrow_Right) then
        local pos = self:getPosition()
        pos.x = pos.x + 0.005 * dt
        self:setPosition(pos)
    end
    if IsKeyDown(Action.N) then
        local pos = self:getPosition()
        pos.y = pos.y + 0.005 * dt
        self:setPosition(pos)
    end
    if IsKeyDown(Action.M) then
        local pos = self:getPosition()
        pos.y = pos.y - 0.005 * dt
        self:setPosition(pos)
    end
end

return Script