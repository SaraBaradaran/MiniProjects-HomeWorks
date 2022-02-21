from __future__ import absolute_import, division, print_function
import sys
from ortools.linear_solver import pywraplp
from ortools.constraint_solver import pywrapcp

def main(NumRange):
    # Creates the model.
    solver = pywrapcp.Solver('CSP is fun!')
    DoubleNumRange = 2*NumRange
    # Variables
    a = [[solver.IntVar(0, NumRange-1,'x[%i][%i]' % (i, j)) for j in range(DoubleNumRange)] for i in range(NumRange)]
    # Constraints     
    for i in range(NumRange):
	    solver.Add(solver.AllDifferent( [a[i][(j*2)+1] for j in range(NumRange)]  ) )

    for i in range(NumRange):
        solver.Add(solver.AllDifferent( [a[i][j*2] for j in range(NumRange)]  ) )


    solver.Add(solver.AllDifferent( [ NumRange*a[i][2*j] + a[i][2*j+1] for i in range(NumRange) for j in range(NumRange)]  ) )

    for j in range(DoubleNumRange):
        solver.Add(solver.AllDifferent( [a[i][j] for i in range(NumRange)] ) )		

    db = solver.Phase( [ a[i][j] for j in range(DoubleNumRange) for i in range(NumRange) ] ,
                        solver.FULLPATHLNS, solver.RELOCATE)
                        #solver.FULLPATHLNS, solver.EQ)
                        #solver.FULLPATHLNS, solver.ASSIGN_MIN_VALUE)
                        #solver.FULLPATHLNS, solver.TWOOPT)
    solver.NewSearch(db)

    # Iterates through the solutions, displaying each.
    num_solutions = 0

    while solver.NextSolution():
        # Displays the solution just computed.
        for i in range(NumRange):
            for j in range(DoubleNumRange):
                print(' {}'.format( a[i][j].Value() +1 ) , end='')
                # if(j % 2 == 0):
                #     print('( {}'.format( a[i][j].Value() +1 ) , end='')
                # else:
                #     print(',{} )'.format( a[i][j].Value() +1 ), end='')
            print()
        print()
        num_solutions += 1
        break
    solver.EndSearch()

    print()
    print("Solutions found:", num_solutions)
    print("Time:", solver.WallTime(), "ms")


NumRange = 3

if __name__ == "__main__":
  if len(sys.argv) > 1:
    NumRange = int(sys.argv[1])
	
  main(NumRange)


