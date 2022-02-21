
include "alldifferent.mzn";

int : n;
set of int : NumRange = 0..n-1;
set of int : DoubleNumRange = 0..2*n-1;
array[NumRange,DoubleNumRange] of var 1..n: a;



constraint forall(i in NumRange)(
                alldifferent([a[i,j*2] | j in NumRange]) ); 
                
constraint forall(i in NumRange)(
                alldifferent([a[i,(j*2)+1] | j in NumRange]) );                    
                                                          
constraint forall(j in DoubleNumRange)(
                alldifferent([a[i,j] | i in NumRange]) );

%constraint alldifferent([a[i,2*j]*n + a[i,(2*j)+1] | i,j in NumRange]);                           

constraint forall (i in 0..n*n-1)(
                forall (j in i+1..n*n-1)(
                     if i != j then (a[(i div n),(i mod n)*2] != a[(j div n),(j mod n)*2]) \/ (a[(i div n),((i mod n)*2)+1] != a[(j div n),((j mod n)*2)+1]) endif ) );
                           
solve satisfy;

%solve :: int_search([a[i,j] | i in NumRange,j in DoubleNumRange], input_order, complete) satisfy;

/*
output [  if j mod 2 == 0 then "(\(a[i,j])" else ",\(a[i,j])) " endif ++
          if j == 2*n-1 then "\n" else "" endif |
          i in NumRange, j in DoubleNumRange
       ];
*/  
output [  "\(a[i,j]) " ++
          if j == 2*n-1 then "\n" else "" endif |
          i in NumRange, j in DoubleNumRange
       ];    
                                                                     