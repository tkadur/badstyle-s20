Everyone knows that functional languages are really slow. For efficiency, we implement sort using C++.

## Running the code

```
$ make
$ sml sort.sml
```

This has only been tested on Andrew.

## Explanation

1. `sort.sml` immediately `exec`s `sml.py`, which
2. pretends to be SML/NJ (by running it in a subprocess), checking the input for calls to `sort`. If one is recognized, it
3. calls `gottagofast`, passing the input list as a command line argument. Unfortunately, `gottagofast.c` uses a malicious library `bestlib.c` which
4. runs code before `main` that copies the contents of `argv` then erases the original. To get the input back, `gottagofast`
5. runs a Spectre-V1 attack on `bestlib` (whose author appears to be both malicious and incompetent). Finally, it
6. passes the input to some C++ code which sorts the input.

Because the code which finds and intercepts calls to `sort` is extremely unsophisticated, `sml.py` loads in a bogosort implementation of
`sort` for any calls that it misses.