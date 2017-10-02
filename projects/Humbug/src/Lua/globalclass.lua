-- write to IO
io.write("IO Write, from globalclass.lua, ",_VERSION,"!\n")
io.write("IO Write, Value myVar:(", myVar, ")!\n")

x=3
myVar = "it Changed really freaky ---"..x

a = testclass('a string')
a:print_string()

dummy:greet()
greet2()

game:print_string()