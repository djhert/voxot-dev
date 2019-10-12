# voxot-dev

To get started, download the repo and init the submodules

```sh
$ git submodule update --init --recursive
```

Ensure that the godot-cpp libraries are built (this will build a debug version)

```sh
$ cd godot-cpp/
$ scons platform=linux use_llvm=yes generate_bindings=yes -j4 bits=64 target=debug
```

Now, you can build the voxot-dev project.  From the project folder:

```sh
$ scons -j4 use_llvm=yes platform=linux target=debug
```

Start Godot in the project folder, and you can now run this project!
