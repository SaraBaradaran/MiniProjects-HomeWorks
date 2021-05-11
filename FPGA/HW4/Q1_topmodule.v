
module game#(parameter N = 8)(First_num, Second_num, Target_num, clk, Reset, winner_clk, Correct_gues, Out_cr, Out_wr, Result);

input [N-1:0] First_num, Second_num, Target_num;
input clk, Reset; 
output winner_clk;
output [1:0] Correct_gues, Out_wr, Result;
output [9:0] Out_cr;

wire winner_clk;
wire [1:0] Correct_gues, Out_wr, Result;
wire [9:0] Out_cr;

defparam u1.N = N;
correlation u1(First_num, Second_num, Target_num, clk, Correct_gues, Out_cr, Reset);
frequency_division u3(clk, Reset, winner_clk);
winner u2(Out_cr, Out_wr, winner_clk);
decision u4(Correct_gues, Out_wr, clk, Result);

endmodule 