
include "alldifferent.mzn";

int : n;
set of int : NumRange = 1..n;
set of int : DoubleNumRange = 1..2*n;
array[1..n,1..2*n] of var NumRange: a;

constraint forall(i in NumRange)(
                alldifferent([a[i,j*2] | j in NumRange]) ); 
                
constraint forall(i in NumRange)(
                alldifferent([a[i,(j*2)-1] | j in NumRange]) );

constraint forall(i in NumRange)(
                forall(j in NumRange)(
                        a[i,(2*j)-1] != a[i,2*j]) ); 

constraint forall(j in DoubleNumRange)(
                alldifferent([a[i,j] | i in NumRange]) );
                
solve satisfy;

output [  if j mod 2 == 1 then "(\(a[i,j])" else ",\(a[i,j])) " endif ++
          if j == 2*n then "\n" else "" endif |
          i in NumRange, j in DoubleNumRange
       ];                                