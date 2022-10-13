--[[
Hammerspon initialization file
--]]

function startZoom()
  hs.application.open("zoom.us", 0, false)
end

function stopZoom()
  local zoom = hs.application.find("zoom.us")
  if (zoom == nil) then return end
  if (zoom:isRunning()) then zoom:kill() end
end

function readHomeControlToken()
  local file = io.open("homecontrol.tkn", "r")
  local token = file:read("*line")
  io.close(file)
  return token
end
local homeControlToken = readHomeControlToken()

function triggerHomeKitScene(sceneName)
  local url = "homecontrol://x-callback-url/run-action?action-type=trigger-scene&item-type=scene&item-name=" .. sceneName ..
              "&home-name=My%20Home&authentication-token=" .. homeControlToken
  hs.execute("open -g \"" .. url .. "\"")
end

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "1", function()
  -- hs.alert.show("Button 1")
  startZoom()
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "2", function()
  -- hs.alert.show("Button 2")
  triggerHomeKitScene("Forest")
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "3", function()
  -- hs.alert.show("Button 3")
  triggerHomeKitScene("Daylight")
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "4", function()
  -- hs.alert.show("Button 4")
  triggerHomeKitScene("Work%20Work%20Work")
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "5", function()
  -- hs.alert.show("Button 1 (long press)")
  stopZoom()
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "6", function()
  -- hs.alert.show("Button 2 (long press)")
  triggerHomeKitScene("Vintage%20Modern")
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "7", function()
  hs.alert.show("Button 3 (long press)")
end)

hs.hotkey.bind({"cmd", "alt", "ctrl"}, "8", function()
  hs.alert.show("Button 4 (long press)")
end)
