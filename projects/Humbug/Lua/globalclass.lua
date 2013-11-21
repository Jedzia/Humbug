-- write to IO
io.write("IO Write, from iowrite.lua, ",_VERSION,"!\n")
io.write("IO Write, Value myVar:(", myVar, ")!\n")
myVar = "it Changed really freaky ---"

a = testclass('a string')
a:print_string()

dummy:greet()
greet2()

game:print_string()