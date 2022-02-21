% Use this editor as a MiniZinc scratch book
include "alldifferent.mzn";

var {3}: c1;
var {2,3}: c2;
var {1,2,3}: c3;
var {1,2,3}: c4;
var {2,3}: c5;

constraint c1 != c2 /\ c2 != c3 /\ c3 != c4 /\ c2 != c4 /\ c3 != c5 /\ c4 != c5;

solve satisfy;
