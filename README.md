# EGRE 591: Compiler Construction
By Charles D. & Dajion M.

# Building

To build run make,
`make`
this will output the toy complier
`bin/tc`

to use the compiler
`./tc`

```
Usage: tc [Function] <input_file>
            -Function      -s        display all Scanner information
            -Function      -p        display all Parser information
            -Function      -a        display all abstract information
            -Function      -c        display all Completed information
```

# Executing
This will pring the Scanner/Lexer information for the toyc file
` ./bin/tc -s new_tests/full.tc`

This will pring the Parser information for the toyc file
` ./bin/tc -p new_tests/full.tc`

This will pring the Abstract Syntax information for the toyc file
` ./bin/tc -a new_tests/full.tc`

This will pring the All the informatino and the .j File information for the toyc file
` ./bin/tc -c new_tests/full.tc`

this will generate a *.j file

use jasmin to generate the *.class file
`java -jar tools/jasmin.jar new_tests/full.j -d new_tests/`

run the java code

```
cd new_tests
java full
```



# Jasmin
https://jasmin.sourceforge.net/guide.html

# Part 1 Lexical Analysis Complete
wip

# Part 2 Syntax Anaysis Complete
wip

# Part 3 Semantic Anaysis + Code Generation Currently wproking
wip
