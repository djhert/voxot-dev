#!python
import os, subprocess, fnmatch
from subprocess import check_call
from sys import exit

opts = Variables([], ARGUMENTS)

# Gets the standard flags CC, CCX, etc.
env = DefaultEnvironment()

# Define our options
opts.Add(EnumVariable('target', "Compilation target", 'debug', ['d', 'debug', 'r', 'release']))
opts.Add(EnumVariable('platform', "Compilation platform", '', ['', 'android', 'windows', 'x11', 'linux', 'osx']))
opts.Add(EnumVariable('p', "Compilation target, alias for 'platform'", '', ['', 'windows', 'x11', 'linux', 'osx']))
opts.Add(BoolVariable('use_llvm', "Use the LLVM / Clang compiler", 'no'))
opts.Add(PathVariable('target_path', 'The path where the lib is installed.', 'lib/'))
opts.Add(PathVariable('target_name', 'The library name.', os.path.basename(os.getcwd()), PathVariable.PathAccept))
opts.Add(EnumVariable(
    'android_arch',
    'android architecture',
    'armv7',
    allowed_values=('armv7', 'arm64v8'),
    ignorecase=2
))


# Local dependency paths, adapt them to your setup
godot_headers_path = "godot-cpp/godot_headers/"
cpp_bindings_path = "godot-cpp/"
cpp_library = "libgodot-cpp"

# only support 64 at this time..
bits = 64

# Updates the environment with the option variables.
opts.Update(env)

# Process some arguments
if env['use_llvm']:
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'

if env['p'] != '':
    env['platform'] = env['p']

if env['platform'] == '':
    print("No valid target platform selected.")
    quit();

# Check our platform specifics
if env['platform'] == "osx":
    env['target_path'] += 'osx/'
    cpp_library += '.osx'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-g','-O2', '-arch', 'x86_64'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    else:
        env.Append(CCFLAGS = ['-O3', '-arch', 'x86_64'])
        env.Append(LINKFLAGS = ['-arch', 'x86_64'])

elif env['platform'] in ('x11', 'linux'):
    env['target_path'] += 'linux/'
    cpp_library += '.linux'
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-fPIC', '-g', '-std=c++17', '-DDEBUG'])
    else:
        env.Append(CCFLAGS = ['-fPIC', '-O3', '-std=c++17'])

elif env['platform'] == "windows":
    env['target_path'] += 'win64/'
    cpp_library += '.windows'
    # This makes sure to keep the session environment variables on windows,
    # that way you can run scons in a vs 2017 prompt and it will find all the required tools
    env.Append(ENV = os.environ)

    env.Append(CCFLAGS = ['-DWIN32', '-D_WIN32', '-D_WINDOWS', '-W3', '-GR', '-D_CRT_SECURE_NO_WARNINGS'])
    if env['target'] in ('debug', 'd'):
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])

elif env['platform'] == "android":
    if "ANDROID_NDK_HOME" not in os.environ:
        raise ValueError(
            'ANDROID_NDK_HOME is not set!'
        )
    # Get num of jobs passed
    num_jobs = "-j"+str(GetOption('num_jobs'))
    if env['android_arch'] ==  'armv7':
        os.environ['SC_ARCH'] = 'armeabi-v7a'
    elif env['android_arch'] == 'arm64v8':
        os.environ['SC_ARCH'] = 'arm64-v8a'
    # Use llvm, not sure if working
    if env['use_llvm']:
        os.environ['SC_CLANG'] = "true"
    else:
        os.environ['SC_CLANG'] = "false"
    # Debug or release flags
    if env['target'] == 'debug':
        os.environ['SC_TARGET'] = "debug"
    else:
        os.environ['SC_TARGET'] = "release"

    # NDK Command
    command = ["ndk-build", num_jobs, "NDK_LIBS_OUT=lib", "NDK_OUT=bin/obj"]
    # Call with env set
    try:
        check_call(command)
    except subprocess.CalledProcessError:
        exit()
    os.remove("lib/"+os.environ['SC_ARCH']+"/libc++_shared.so")
    # Exit script, all done
    exit()


if env['target'] in ('debug', 'd'):
    cpp_library += '.debug'
else:
    cpp_library += '.release'

cpp_library += '.' + str(bits)

# make sure our binding library is properly includes
env.Append(CPPPATH=['.', godot_headers_path, cpp_bindings_path + 'include/', cpp_bindings_path + 'include/core/', cpp_bindings_path + 'include/gen/'])
env.Append(LIBPATH=[cpp_bindings_path + 'bin/'])
env.Append(LIBS=[cpp_library])

# Add the folder for the C++ source
env.Append(CPPPATH=['source/'])

def GlobRecursive(pattern, node='.'):
    matches = []
    for root, dirnames, filenames in os.walk(node):
        for filename in fnmatch.filter(filenames, pattern):
            matches.append(os.path.join(root, filename))
    return matches

# Use the recursive globber to compile all source in folder
sources = GlobRecursive('*.cpp', 'source')

# Use this to compile all files in folder
## sources = Glob('src/*.cpp')

library = env.SharedLibrary(target=env['target_path'] + env['target_name'] , source=sources)

Default(library)

# Generates help for the -h scons option.
Help(opts.GenerateHelpText(env))

