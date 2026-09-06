# COS214 Practical 4

Binary is `taskforge`. Needs g++, make. GDB and Valgrind are linux (WSL or the docker image). If `docker build` dies with `npipe:////./pipe/docker_engine` then Docker Desktop isnt running — start it and wait for the engine.

## Local (linux / WSL)

```
make
./taskforge
make run
make mem
make gdb
make clean
```

`make mem` dumps the valgrind report into `memory.log`. Makefile already compiles with `-g` so gdb can see symbols.

GDB for the iterator walk:

```
gdb ./taskforge
(gdb) break TGIterator::operator++
(gdb) run
(gdb) print (*current)->getDescription()
(gdb) continue
```

GDB for a state / decorator update:

```
gdb ./taskforge
(gdb) break TaskDecorator::updateState
(gdb) break Design::updateState
(gdb) run
(gdb) backtrace
```

## Docker

```
docker build -t taskforge .
docker run --rm taskforge
```

Default cmd is `./taskforge`. For make / gdb you have to override the entrypoint.

```
docker run --rm --entrypoint make taskforge mem
docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --entrypoint gdb taskforge ./taskforge
```

ptrace is for gdb/valgrind inside the container.

Image has g++, make, gdb and valgrind. Source is `include/` + `src/`, same makefile as the repo.
