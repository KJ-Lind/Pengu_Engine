local Script = {}

Script.rotspeed = math.random() * 0.005

function Script:onStart()
    print("Entity script started")
end

function Script:onUpdate(dt)
    local rot = self:getRotation()
    rot.z = rot.z - Script.rotspeed * dt
    self:setRotation(rot)
end

return Script