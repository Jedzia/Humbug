-- write to IO
io.write("IO Write, from sprite.lua, ",_VERSION,"!\n")
-- io.write("IO Write, Value X1:(", X1, ")!\n")
-- X1=X1 + 1

-- io.write("IO Write, Value Host:(", Host, ")!\n")
io.write("IO Write, Value Host.X1:(", Host.X1, ")!\n")
Host.X1 = Host.X1 + 1
