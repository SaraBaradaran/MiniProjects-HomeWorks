module Mux4input_1bit_TestBench;

reg in0, in1, in2, in3;
reg [1:0] select;
wire out;

Mux4input_1bit component(in0, in1, in2, in3, out, select);
initial begin

	$monitor(" in0 = %b, in1 = %b, in2 = %b, in3 = %b, select = %b, out = %b", in0, in1, in2, in3, select, out);
	#20
	in0 = 1'b0;
	in1 = 1'b1;
	in2 = 1'b0;
	in3 = 1'b1;
	select = 2'b00;
	#20
	in0 = 1'b0;
	in1 = 1'b1;
	in2 = 1'b0;
	in3 = 1'b1;
	select = 2'b01;
	#20
	in0 = 1'b0;
	in1 = 1'b1;
	in2 = 1'b0;
	in3 = 1'b1;
	select = 2'b10;
	#20
	in0 = 1'b0;
	in1 = 1'b1;
	in2 = 1'b0;
	in3 = 1'b1;
	select = 2'b11;
	#20
	in0 = 1'b1;
	in1 = 1'b0;
	in2 = 1'b1;
	in3 = 1'b0;
	select = 2'b00;
	#20
	in0 = 1'b1;
	in1 = 1'b0;
	in2 = 1'b1;
	in3 = 1'b0;
	select = 2'b01;
	#20
	in0 = 1'b1;
	in1 = 1'b0;
	in2 = 1'b1;
	in3 = 1'b0;
	select = 2'b10;
	#20
	in0 = 1'b1;
	in1 = 1'b0;
	in2 = 1'b1;
	in3 = 1'b0;
	select = 2'b11;

end

endmodule
