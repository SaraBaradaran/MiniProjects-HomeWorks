
module Mux16input_8bit_TestBench;

reg [7:0] in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15;
wire [7:0] out;
reg [3:0] select;

Mux16input_8bit component(in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, out, select);

initial begin

	#5
	in0 = 8'b0000_0000;
	in1 = 8'b0000_0001;
	in2 = 8'b0000_0010;
	in3 = 8'b0000_0011;
	
	in4 = 8'b0000_0100;
	in5 = 8'b0000_0101;
	in6 = 8'b0000_0110;
	in7 = 8'b0000_0111;

	in8 = 8'b0000_1000;
	in9 = 8'b0000_1001;
	in10 = 8'b0000_1010;
	in11 = 8'b0000_1011;

	in12 = 8'b0000_1100;
	in13 = 8'b0000_1101;
	in14 = 8'b0000_1110;
	in15 = 8'b0000_1111;

	select = 4'b0000;
	#60
	select = 4'b0001;
	#60
	select = 4'b0010;
	#60
	select = 4'b0011;
	#60
	select = 4'b0100;
	#60
	select = 4'b0101;
	#60
	select = 4'b0110;
	#60
	select = 4'b0111;
	#60
	select = 4'b1000;
	#60
	select = 4'b1001;
	#60
	select = 4'b1010;
	#60
	select = 4'b1011;
	#60
	select = 4'b1100;
	#60
	select = 4'b1101;
	#60
	select = 4'b1110;
	#60
	select = 4'b1111;

end

endmodule 