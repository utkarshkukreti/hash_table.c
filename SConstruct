env = Environment()

cflags = ["-Wall", "-pedantic", "-std=c99"]

# Debug flags on by default for now.
cflags += ["-g", "-O0"]

env.Append(CFLAGS=cflags)

env.Program("bin/test",
        Glob("src/*.c") +
        Glob("test/*.c"))
