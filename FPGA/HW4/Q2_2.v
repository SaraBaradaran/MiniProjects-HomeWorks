
module RFCorrelator(bit_stream, clk, reset, Target_Num,
num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16, Out_str);

output [31:0] Target_Num;
input clk, reset, bit_stream;
output [3:0] Out_str;

input [31:0] num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16;

reg [31:0] shift_reg;
reg [5:0] current_bit;
reg [31:0] Target_Num;

wire [3:0] Out_4;
correlation_32 u(num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16, Target_Num, clk, reset, Out_4);

assign Out_str = Out_4;

always@(posedge clk)
begin
	if(reset)
	begin
		shift_reg <= 0;
		current_bit <= 0;
	end
	else if(current_bit < 32)
	begin
		shift_reg <= shift_reg >> 1;
		shift_reg[31] <= bit_stream;
		current_bit <= current_bit + 1;
	end
	else
	begin
		Target_Num <= shift_reg;
		shift_reg <= 0;
		current_bit <= 0;	
	end

end

endmodule 