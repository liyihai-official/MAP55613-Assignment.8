# MAP55613-C-Programming
This is the assignment solutions of MAP55613 C Program, the module in Trinity College Dublin.

Description: In this assignment, the two programs are solving the one dimension heat equation from $[0, 1]$ in $0$ to $0.2$ seconds which is 
$\[\frac{\partial}{\partial t}u(t,x) =  \frac{\partial^2}{\partial u^2}u(t,x) \]$
The initial condition is 
\[ u(0,x) = sin(\pi x) \]
and the boundary conditions are 
$\[ u(t,0) = u(t,1) = 0 \]$

Solved it by iterating as 
\[ u(x, t + \Delta t) =  \left[ u(x+ \Delta x, t) + u(x-\Delta x, t) \right]\frac{1}{2}@f\]

## Features 
- Assignment8a is the single thread version
- Assignment8b is the single thread version
