module Mux4input_1bit(in0, in1, in2, in3, out, select);

input in0, in1, in2, in3;
input [1:0] select;
output out;
reg out;

always @(in0, in1, in2, in3, select) begin

case(select)

0: out = in0;
1: out = in1;
2: out = in2;
3: out = in3;

endcase
end

endmodule
