-- basic function declaration
double x = x + x


-- recursion
quadruple x = double (double x) -- calls double function twice


-- if else statement
smallest x y = if x < y then x else y
largest x y = if x > y then x else y


diff x y = l - s
           where
              l = largest x y
              s = smallest x y
            