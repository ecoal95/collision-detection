# Simple collision-detection library

This is intended to be a simple static library for collision detection in 2d
convex polygons.

The main reason for the existance of this repo is that I wanted to use collision
detection in my work for the graphical user interfaces subject in my university.

Since it has to be implemented both in Cocoa and C# I preferred to have simple
libraries with the reusable logic and a very low_level interface.

Maybe I add support for circles later, as well as a friction calculation
function as well as bounce factor.

## Usage

To compile the static library simply run `make`. This will build the library
**without optimisations**.

To build the library with optimisations, you can use:

```
$ make release
```

You can add more flags using `CC_FLAGS`. I haven't benchmarked it with and
without `-ffastmath`, but that could be a good idea...

To run the tests (very simple at the moment):

```
$ make test
```
