local bus_stop = Image("bus_stop.jpg")
local ext_aidpost_day = Image("ext_aidpost_day.jpg")
local ext_bus = Image("ext_bus.jpg")
local spr = Sprite("normal.png")
local shizyka_smile = Sprite("shizyka_smile.png")

local TestCharacter = Character("Test Character")
local Dezlow = Character("Dezlow")

function label_start()
    scene(ext_aidpost_day)
    spr:show()
    shizyka_smile:show()
    TestCharacter "Hello,\n World!"
    spr:hide()
    shizyka_smile:hide()
    TestCharacter "Hello, World! Hello, World!"
    scene(bus_stop)
    shizyka_smile:show()
    spr:show()
    Dezlow "Hello, ¿‡‡!"
    scene(ext_bus)
    Dezlow "Hello, World!"
end
