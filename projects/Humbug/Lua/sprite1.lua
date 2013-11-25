-- write to IO
io.write("IO Write, from sprite.lua, ",_VERSION,"!\n")
-- io.write("IO Write, Value X1:(", X1, ")!\n")
-- X1=X1 + 1

-- io.write("IO Write, Value Host:(", Host, ")!\n")
io.write("IO Write, Ticks=", Host.Ticks, " Value Host.X/Y:(", Host.X, "/", Host.Y, ")!\n")

--World = {}
--World.ScreenX = 1024
--World.ScreenY = 768
--World.FPS = 30

speed = -2.0
Host.X = (World.ScreenX/2) + math.sin(Host.Ticks/World.FPS * speed) * (World.ScreenX/3)
Host.Y = (World.ScreenY/2) + math.cos(Host.Ticks/World.FPS * speed) * (World.ScreenY/3)
