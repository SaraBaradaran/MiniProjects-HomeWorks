from __future__ import absolute_import
from __future__ import division
from __future__ import print_function


import sys
from ortools.sat.python import cp_model


class VarArraySolutionPrinter(cp_model.CpSolverSolutionCallback):

    def __init__(self, variables):
        cp_model.CpSolverSolutionCallback.__init__(self)
        self.__variables = variables
        self.__solution_count = 0

    def on_solution_callback(self):
        self.__solution_count += 1
        for v in self.__variables:
            print('%s=%i' % (v, self.Value(v)), end=' ')
        print()

    def solution_count(self):
        return self.__solution_count


def main(NumRange):
    # Creates the model.
    model = cp_model.CpModel()
    DoubleNumRange = 2*NumRange
    # Variables
    a = [[model.NewIntVar(1, NumRange,'x[%i][%i]' % (i, j)) for j in range(DoubleNumRange)] for i in range(NumRange)]
    # Constraints     
    for i in range(NumRange):
        model.AddAllDifferent( [a[i][(j*2)+1] for j in range(NumRange)]  )
		
    for i in range(NumRange):
        model.AddAllDifferent( [a[i][j*2] for j in range(NumRange)]  )

    for i in range(NumRange):
	    for j in range(NumRange):
		    model.Add( a[i][2*j] != a[i][(2*j)+1] )
		
    for j in range(DoubleNumRange):
        model.AddAllDifferent( [a[i][j] for i in range(NumRange)]  )			

    # Create a solver and solve.
    solver = cp_model.CpSolver()

    # Sets a time limit of 60 seconds.
    solver.parameters.max_time_in_seconds = 60.0

    status = solver.Solve(model)

    if status == cp_model.OPTIMAL:
        for i in range(NumRange):
            for j in range(DoubleNumRange):
                if(j % 2 == 0):
                    print('( %i' % solver.Value(a[i][j]), end='')
                else:
                    print(',%i )' % solver.Value(a[i][j]), end='')
            print()

NumRange = 3

if __name__ == "__main__":
  if len(sys.argv) > 1:
    NumRange = int(sys.argv[1])
  main(NumRange)
