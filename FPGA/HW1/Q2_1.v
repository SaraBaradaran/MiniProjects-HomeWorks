module SequenceDetector(input_seq, seq_select, sequence_detected, Dseq_number, clk);

input input_seq, clk;
input [1:0] seq_select; 
output sequence_detected;
output [7:0] Dseq_number;

reg [7:0] w = 0;

parameter [2:0] s0 = 3'b000, s1 = 3'b001, s2 = 3'b010, s3 = 3'b011, s4 = 3'b100;
//00 = 4'b1100, 01 = 4'b1010, 10 = 4'b0110, 11 = 4'b1001;

reg [2:0] current_state = s0;

always @(seq_select) begin

current_state = s0;
w = 0;

end
always @(posedge clk) begin

case (seq_select)

0:
	case(current_state)

	s0: if(input_seq) current_state <= s1; else current_state <= s0;
	s1: if(input_seq) current_state <= s2; else current_state <= s0;
	s2: if(input_seq) current_state <= s2; else current_state <= s3;
	s3: if(input_seq) current_state <= s1; else begin current_state <= s4; w = w + 1; end
	s4: if(input_seq) current_state <= s1; else current_state <= s0;

	endcase
1:
	case(current_state)
	
	s0: if(input_seq) current_state <= s1; else current_state <= s0;
	s1: if(input_seq) current_state <= s1; else current_state <= s2;
	s2: if(input_seq) current_state <= s3; else current_state <= s0;
	s3: if(input_seq) current_state <= s1; else begin current_state <= s4; w = w + 1; end
	s4: if(input_seq) current_state <= s3; else current_state <= s0;

	endcase
2:
	case(current_state)
	
	s0: if(input_seq) current_state <= s0; else current_state <= s1;
	s1: if(input_seq) current_state <= s2; else current_state <= s1;
	s2: if(input_seq) current_state <= s3; else current_state <= s1;
	s3: if(input_seq) current_state <= s0; else begin current_state <= s4; w = w + 1; end
	s4: if(input_seq) current_state <= s2; else current_state <= s1;

	endcase
3:
	case(current_state)
	
	s0: if(input_seq) current_state <= s1; else current_state <= s0;
	s1: if(input_seq) current_state <= s1; else current_state <= s2;
	s2: if(input_seq) current_state <= s1; else current_state <= s3;
	s3: if(input_seq) begin current_state <= s4; w = w + 1; end else current_state <= s0;
	s4: if(input_seq) current_state <= s1; else current_state <= s2;
	
	endcase
	
endcase
end 

	assign sequence_detected = (current_state == s4) ? 1:0;
	assign Dseq_number = w;
endmodule 