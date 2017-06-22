--Step function
function step()
   randF = randForce(20)
   proximityF = proximityAvoidanceForce()
   camF = cameraForce()

   sumForce = { x = 0, y = 0 }
   sumForce.x = randF.x + proximityF.x
   sumForce.y = randF.y + proximityF.y

   speedFromForce(sumForce)
end


function init()
    robot.colored_blob_omnidirectional_camera.enable()
end

--nothing to reset
function reset()
end

--nothing to destroy
function destroy()
end


function speedFromForce(f)
   forwardSpeed = f.x * 1.0
   angularSpeed = f.y * 0.3

   leftSpeed  = forwardSpeed - angularSpeed
   rightSpeed = forwardSpeed + angularSpeed

   robot.wheels.set_velocity(leftSpeed,rightSpeed)
end


function randForce(val)
   angle = robot.random.uniform(-math.pi/2, math.pi/2)
   randomForce = {x = val * math.cos(angle), y = val * math.sin(angle) }
   return randomForce
end


function proximityAvoidanceForce()
   avoidanceForce = {x = 0, y = 0}

   for i = 1, 24 do
      v = -100 * robot.proximity[i].value
      a = robot.proximity[i].angle

      sensorForce = { x = v * math.cos(a), y = v * math.sin(a) }
      avoidanceForce.x = avoidanceForce.x + sensorForce.x
      avoidanceForce.y = avoidanceForce.y + sensorForce.y
   end

   return avoidanceForce
end


function cameraForce(attraction, strong)
  camForce = {x = 0, y = 0}

  -- Check if there is a light seen
  if(#robot.colored_blob_omnidirectional_camera == 0) then
    return camForce
  end

  for i = 1, 24 do
     d = robot.colored_blob_omnidirectional_camera[i].distance
     a = robot.colored_blob_omnidirectional_camera[i].angle

     -- strong repulsion
     v = 35 * d/80
     v = -v

     sensorForce = { x = v * math.cos(a), y = v * math.sin(a) }
     camForce.x = camForce.x + sensorForce.x
     camForce.y = camForce.y + sensorForce.y
  end

  return camForce
end


-- Helper Functions
function table.print(t)
   for key,value in pairs(t) do
      log(key .. " -> " .. value)
   end
end
