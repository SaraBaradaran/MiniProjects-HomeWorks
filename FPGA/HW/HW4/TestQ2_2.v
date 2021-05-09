module RFCorrelator_tb;

reg clk, reset, bit_stream;
wire [31:0] Target_Num;
reg [31:0] num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16;
integer i;

wire [3:0] Out_str;
RFCorrelator u(bit_stream, clk, reset, Target_Num, num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16, Out_str);



initial
begin

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
reset = 1;

#45
reset = 0;
bit_stream = 1;
#20 

bit_stream = 0;
#20 

bit_stream = 0;
#20 

bit_stream = 1;
#20 

bit_stream = 0;
#20 

bit_stream = 1;
#20 

bit_stream = 0;

end

initial 
begin
clk = 0;
forever
#10 clk = ~clk;
end
endmodule
