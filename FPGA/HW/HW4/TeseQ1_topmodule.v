

module game_tb;


reg [5:0] First_num, Second_num, Target_num;
reg clk, Reset; 
wire [1:0] Result;

wire winner_clk;

wire [1:0] Correct_gues, Out_wr;
wire [9:0] Out_cr;

defparam u.N = 6;
game u(First_num, Second_num, Target_num, clk, Reset, winner_clk, Correct_gues, Out_cr, Out_wr, Result);
initial
begin

Reset = 1;

#100
Reset = 0;

#40
Target_num = 6'b010101;

First_num =  6'b010111; //c = 5
Second_num = 6'b000101;// c = 5

#20
First_num = 6'b101001; //2
Second_num = 6'b010000; //4

#20
First_num = 6'b010111; //5
Second_num = 6'b010111;//5

#20
First_num = 6'b000101;//5
Second_num = 6'b010000;//4

#20
First_num = 6'b010110;//4
Second_num = 6'b010111;//5

#20
Reset = 1;

/*
Reset = 1;

#100
Reset = 0;

#48
Target_num = 6'b010101;

First_num =  6'b011101; //c = 5
Second_num = 6'b000101;// c = 5

#100
First_num = 6'b101001; //2
Second_num = 6'b010000; //4

#100
First_num = 6'b010111; //5
Second_num = 6'b111101;//4

#100
First_num = 6'b010111;//5
Second_num = 6'b010100;//5

#100
First_num = 6'b110001;//4
Second_num = 6'b010111;//5

*/

end

initial
begin
clk = 0;

forever 
#10 clk = ~clk;

end



endmodule 