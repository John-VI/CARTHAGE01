# Credit to the Endless Sky guys, a lot of this is from their SConstruct file.
# Really love that game too.

import os
import platform

import os.path

is_windows_host = platform.system().startswith('Windows')
scons_toolset = ['mingw' if is_windows_host else 'default']
env = DefaultEnvironment(tools = scons_toolset, ENV = os.environ, COMPILATIONDB_USE_ABSPATH=True)

if 'CXX' in os.environ:
	env['CXX'] = os.environ['CXX']
if 'CXXFLAGS' in os.environ:
	env.Append(CCFLAGS = os.environ['CXXFLAGS'])
if 'LDFLAGS' in os.environ:
	env.Append(LINKFLAGS = os.environ['LDFLAGS'])
if 'AR' in os.environ:
	env['AR'] = os.environ['AR']

if is_windows_host:
	env.Append(LINKFLAGS = ["-mwindows"])

opts = Variables()
opts.AddVariables(
	EnumVariable("mode", "Compilation mode", "debug", allowed_values=("release", "debug")),
	PathVariable("BUILDDIR", "Directory to store compiled object files in", "sconsbuild", PathVariable.PathIsDirCreate),
	PathVariable("BIN_DIR", "Directory to store binaries in", "sconsbuild", PathVariable.PathIsDirCreate)
)
opts.Update(env)
Help(opts.GenerateHelpText(env))

flags = ["-Wall", "-pedantic", "-fdiagnostics-color=always"]
if env["mode"] == "debug":
	flags += ["-ggdb"]
elif env["mode"] == "release":
	flags += ["-O3"] # WHOA, YEAH
env.Append(CCFLAGS = flags)
env.Append(CXXFLAGS = flags)

game_libs = ["mingw32", "SDL2main", "SDL2", "SDL2_image", "pthread"]
env.Append(LIBS = game_libs)

builddir = env["BUILDDIR"]
bindir = env["BIN_DIR"]

# This function is basically useless and unfinished right now but if we add subdirs it saves a tiny bit of effort.
def RecursiveGlob(pattern, dir_name=builddir):
	matches = env.Glob("C:\\Users\\dogja\\Projects\\C++\\caulk-", pattern)
	return matches

rust = env.Program(os.path.join(bindir, "rusting"), ["clkfont.cpp", "clkinputman.cpp", "clkinputtrigger.cpp", "clkkeybind.cpp", "clkterminator.cpp", "clktex.cpp", "clkwin.cpp", "grid.cpp", "monster.cpp", "tile.cpp", "clkviewport.cpp",
"main.cpp"])
env.Default(rust)
