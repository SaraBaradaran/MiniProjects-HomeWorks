module SequenceDetector_TestBench;

reg input_seq, clk;
reg [1:0] seq_select;
wire sequence_detected;
wire [7:0] Dseq_number;

SequenceDetector component(input_seq, seq_select, sequence_detected, Dseq_number, clk);

//00 = 4'b1100, 01 = 4'b1010, 10 = 4'b0110, 11 = 4'b1001;
initial begin

	#11
	input_seq = 1'b0;
	seq_select = 2'b00;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b0;
	#88
	input_seq = 1'b1;
	seq_select = 2'b01;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b0;
	#88
	input_seq = 1'b0;
	seq_select = 2'b10;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b1;
	#44
	input_seq = 1'b0;
	#88
	input_seq = 1'b1;
	seq_select = 2'b11;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b0;
	#44
	input_seq = 1'b1;
end
initial begin
	$monitor("%d , input_seq = %b, seq_select = %b, sequence_detected = %b, Dseq_number = %b",$time, input_seq, seq_select, sequence_detected, Dseq_number); 
	clk = 0;
	forever #22 clk = ~clk;

end
endmodule 
