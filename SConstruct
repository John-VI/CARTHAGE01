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
	PathVariable("BUILDDIR", "Directory to store compiled files in", "sconsbuild", PathVariable.PathIsDirCreate),
	#PathVariable("BIN_DIR", "Directory to store binaries in", "sconsbuild", PathVariable.PathIsDirCreate)
)
opts.Update(env)
Help(opts.GenerateHelpText(env))

flags = ["-Wall", "-pedantic", "-fdiagnostics-color=always", "-I.", "-std=gnu++20"]
if env["mode"] == "debug":
	flags += ["-ggdb"]
elif env["mode"] == "release":
	flags += ["-O3"] # WHOA, YEAH
env.Append(CCFLAGS = flags)
env.Append(CXXFLAGS = flags)

game_libs = ["SDL2main", "SDL2", "SDL2_image", "pthread"]
if is_windows_host:
    game_libs.Append("mingw32")

env.Append(LIBS = game_libs)

builddir = env["BUILDDIR"]

# This function is basically useless and unfinished right now but if we add subdirs it saves a tiny bit of effort.

env.Tool('compilation_db')
cdb = env.CompilationDatabase('compile_commands.json')
Alias('cdb', cdb)

Export('env os')

SConscript('src/SConscript', variant_dir=builddir)

Clean(env['rusting'], Glob(os.path.join(builddir, "*.cpp")))
Clean(env['rusting'], Glob(os.path.join(builddir, "*.h")))

env.Default(env["rusting"])
