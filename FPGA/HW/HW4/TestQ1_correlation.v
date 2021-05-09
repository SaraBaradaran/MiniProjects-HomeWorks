module cal_correlation_tb;

reg [5:0] First_num, Second_num, Target_num;
reg clk, reset; 
wire [1:0] Correct_gues;
wire [9:0] Out_cr;



defparam u.N = 6;
correlation u(First_num, Second_num, Target_num, clk, Correct_gues, Out_cr, reset);


initial
begin



reset = 1;
Target_num = 6'b010101;

First_num =  6'b010101; //c = 6
Second_num = 6'b000101;// c = 5

#55
reset = 0;

#20
First_num = 6'b101001; //2
Second_num = 6'b010000; //4

#20
First_num = 6'b010111; //5
Second_num = 6'b010101;//6

#20
First_num = 6'b010101;//6
Second_num = 6'b010101;//6

#20
First_num = 6'b010101;//6
Second_num = 6'b010111;//5

#20
Target_num = 6'b110101;




end

initial
begin
clk = 0;

forever 
begin
#10 clk = ~clk;

end
end

endmodule
