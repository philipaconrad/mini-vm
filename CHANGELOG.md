# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased][unreleased]
### Added
- RPN calculator example.

### Changed
- Moved examples to their own directory, `/examples`.


## [0.0.2] - 2015-04-04
### Added
- `CHANGELOG`. This file is intended to document **for humans** what has changed since last version.
- MSVC version of `stdint.h` from [msinttypes](https://msinttypes.googlecode.com/svn/trunk/stdint.h). This allows use of declarations from `stdint.h`, even on obsolete MSVC compiler versions. I use MSVC at school, so this one is important to me.
- `params.txt` file under `/tools`. This file contains the inputs to the bytecode generator script. It was created during the big tools fixup.
- Makefile includes new commands `inspect` and `lib`, which allow looking inside the bytecode format, and building mini-vm as a library, respectively.

### Changed
- `Makefile` improved stylistically.
- All specialized integer sizes (notably 32-bit integers) now follow C99 standard naming conventions. Basically all the "uint32" declarations became "uint32_t" declarations. This was done to increase standards conformance and allowed the removal of `types.h`.
- `stepVMContext()` now takes **2** parameters instead of 1. This virtually forces the program counter to exist outside of the registers. This move was made in the interest of portability and flexibility. Previously, register 0 was implicitly the program counter (which was pretty hacky), and meant that *register size == pointer size*. With the pointer separated from the registers, 32 and 64-bit platforms can compile with exactly the same code.
- `bc.py` now takes a list of unsigned integers instead of the confusing tuples format used in earlier versions. Code size dramatically shrank as a result.

### Removed
- Erlang bytecode generation script `bc.erl`. I pulled this out to reduce future maintenance burden on myself.
- All bytecode generator shell scripts. These are no longer necessary.
- `types.h`. This file was a hacky attempt at what `stdint.h` was doing. It needed to go.
- Unnecessary typecasting in `minivm.c` and `example.c`. There were incredible horrors in there like `&*(uint32*)ctx->r[0].value;`. I'm still scratching my head at why 2 years ago I thought those typecasts were necessary. 

### Fixed
- 64-bit build issues caused by *implicitly* 32-bit pointers in the earlier API is now resolved. (The API was changed so that the program counter's pointer does not depend on VM register size.)


[unreleased]: https://github.com/philipaconrad/mini-vm/compare/v0.0.2...HEAD
[0.0.2]: https://github.com/philipaconrad/mini-vm/compare/v0.0.1...v0.0.2
