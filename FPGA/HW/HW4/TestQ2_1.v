
module correlation_32_tb;

reg clk, Reset;
reg [31:0] Target_Num,
num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16;
wire [3:0] Out_4;

correlation_32 u(num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16, Target_Num, clk, Reset, Out_4);



initial
begin

Reset = 1;

#50
Reset = 0;
num_1 = 1;
num_2 = 2;
num_3 = 3;
num_4 = 4;
num_5 = 5;
num_6 = 6;
num_7 = 7;
num_8 = 8;
num_9 = 9;
num_10 = 10;
num_11 = 11;
num_12 = 12;
num_13 = 13;
num_14 = 14;
num_15 = 15;
num_16 = 16;

Target_Num = 1;

#15
Target_Num = 2;
num_3 = 2;
#20
Target_Num = 3;
num_5 = 3;
num_3 = 3;
#20
Target_Num = 4;

#20
Target_Num = 5;

#20
Target_Num = 6;

#20
Target_Num = 7;

end


initial
begin
clk = 0;
forever
#10 clk = ~clk;
end
endmodule 