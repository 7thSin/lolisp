# Lolisp
Libre and Open Lisp

A lisp dialect focused at functional programming.

The project is still at an early stage, but quickly growing.

The following description applies to the current state of the project, not the
final design.

You can find some examples in the examples folder.
For a complete list of commands and how to use them, see src/builtins/include.h
and src/lisp/stdlib.loli.

## Interpreter

The interpreter is written in C++ for the core part, while most of the functions
are implemented in the Lolisp language itself.
Source code is compiled by the lisp_tree() function to produce a tree of objects
that can be then evaluated, modified, or rebuilt into source code at any time.
Everything in Lolisp is represented by a common structure, with the following properties:

* type, that describes how the object is evaluated:
    - Nil (Never evaluated)
    - Atom (evaluates to itself)
    - List (evaluates to a function call or itself)
* trait, that describes how to evaluate the content of the object:
    - Uint, Int, Float, Char (Numeric types)
    - Symbol
    - Lambda (Lisp function)
* car and cdr, as usual.

Some of the usual types of objects are represented by combinations of type and trait,
e.g. strings are list/char, functions are list/lambda.

The core set of functions is written in C, while Lisp functions are list/lambda 
objects on top of the core functions.

Every object is garbage collected on request with a custom mark-and-sweep 
garbage collector. Currently, garbage collection is triggered at the end of each
cycle of the repl, and after initial compilation.

Self tail calls can be optimized with (recur), so it's possible to write faster
recursive functions without fear of a stack overflow.

The interface uses GNU Readline with completion capabilities for symbols.

See src/opts.cpp for command-line arguments.

## Language

The language is inspired by both Common Lisp and Scheme, with the main difference
being Haskell-inspired non-strict evaluation.
Functional programming is encouraged. Recursive and continuation styles are favoured.
It's possible though to use a more imperative style, being Lolisp a general-purpose language.
Symbols are resolved in a dynamic scope, so Lolisp searches in the current environment
for an occurrence of the symbol, and replaces with the bound objects. If no objects
are found in any scope, the symbol, being an atom, evaluates to itself.
This allows for partially-applicable functions, lambda capture and lazy evaluation of symbols.

## Important notes

* there's little error checking at the moment, so some weird stuff may
happen if you pass wrong arguments to some functions. This will change in the future,
as it takes time to update the builtin functions to support that.
Some functions invoke the debugger on error, that lets you replace the faulty
object with a new one.
* some compilers (namely, gcc 4.8.x and previous, some clang versions) do NOT
support c++14 and/or std::regex. For gcc, 4.9+ provides full support, while clang
compilers with full c++14 support are most likely to support them.
Every other compiler may not be able to compile Lolisp, or make Lolisp throw an
exception on std::regex. Update your compiler, for your own good.
* tested to work on Linux, FreeBSD and OS X. No Windows support. Ever.

## License

Released under GPLv2.

## Author and contributors

Written by Rei <https://github.com/sovietspaceship>

Thanks to:
Lain <https://github.com/serialexperiments> for his invaluable contributions, tests, and suggestions.
