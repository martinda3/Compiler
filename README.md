# EGRE 591: Compiler Construction
By Charles D. & Dajion M.

# Part 2 feature/prettyprinting
as of 10/29/19 it works
runing
bin/tc -v test/while1.tc
generates the abstract systax stuff
TODO
add comma for abstract systax & test
I added comments


Most substational change I made to AS was to the Type() fuction
# Output as of rightnoe
'''
<< Abstract Syntax >>
program(
 sourceCodeFile(test/while1.tc),
 [
  funDef(
   int isEven,
   varDef(int n),
   blockStatement[
    ifStatement{
     expr(
      operator(0)
      number(0)
      expr(
       operator(2)
       number(2)
       no_type(n)
      )
     )
     returnStatement(
      number(1)
     )
     returnStatement(
      number(0)
     )
     }
   ],
  )

  funDef(
   int main,
   blockStatement[
    varDef(int i)
    exprStatement(
     expr(
      operator(1)
      number(1)
      no_type(i)
     )
    )
    whileStatement(
     expr(
      operator(10)
      number(10)
      no_type(i)
     )
     blockStatement[
      writeStatement(
       funcCall(
        no_type(i)
       )

      )

      ifStatement{
       funcCall(
        no_type(isEven)

        funcCall(
         no_type(i)
        )
       )

       writeStatement(
        funcCall(
         string(" is even")
        )

       )
       writeStatement(
        funcCall(
         string(" is odd")
        )

       )
       }

      exprStatement(
       no_type(newline)
      )
      exprStatement(
       expr(
        operator(i)
        expr(
         operator(1)
         number(1)
         no_type(i)
        )
        no_type(i)
       )
      )     ]
     )
    returnStatement(
     number(0)
    )
   ],
  )

 ]
)
<< Abstract Syntax >>

'''


