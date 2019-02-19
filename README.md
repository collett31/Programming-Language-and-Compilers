# Programming-Language-and-Compilers
This is a compiler that we are creating following the following specifications. 


Develop a compiler/interpreter following the following grammar:
<program> -> begin <stmt_list> end
  
<stmt_list> -> <stmt>; | <stmt>; <stmt_list>
  
<stmt> - > <var>=<expression> | input <var> | display <var> | display "string" |
  
<var> -> A | B | C 
  
<expression> -> <var> + <var> | <var>-<var> | <var>*<var> | <var>/<var> | <var>

