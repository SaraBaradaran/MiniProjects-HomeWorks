package com.company;
import org.chocosolver.solver.Model;
import org.chocosolver.solver.variables.IntVar;
import org.chocosolver.solver.Solver;

public class Main {

    public static void Choco()
    {
        int N = 8;

        System.out.println(N);
        Model model = new Model("Nqueen");
        //IntVar[] queen = model.intVarArray("Q", N, 0, N-1); // Variables

        IntVar[] vars = new IntVar[N];
        IntVar[] diag1 = new IntVar[N];
        IntVar[] diag2 = new IntVar[N];

        for (int i=0; i<N; i++)
        {
                vars[i] = model.intVar("Q_" + i, 1, N, false);
                diag1[i] = model.intOffsetView(vars[i], i);
                diag2[i] = model.intOffsetView(vars[i], -i);
        }

        model.allDifferent(vars, "BC").post();
        model.allDifferent(diag1, "BC").post();
        model.allDifferent(diag2, "BC").post();


        Solver solver = model.getSolver();
        if(solver.solve())
        {
            for (int i=0; i<N; i++)
            {
                System.out.printf("%2d  ", vars[i].getValue()); 
            }
            System.out.println();
        }

    }

    public static void main(String[] args) {
        Choco();
    }
}
