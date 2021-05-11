module Mux4input_8bit(in0, in1, in2, in3, out, select);

input [7:0] in0, in1, in2, in3;
output [7:0] out;
input [1:0] select;

Mux4input_1bit U0(in0[0], in1[0], in2[0], in3[0], out[0], select);
Mux4input_1bit U1(in0[1], in1[1], in2[1], in3[1], out[1], select);
Mux4input_1bit U2(in0[2], in1[2], in2[2], in3[2], out[2], select);
Mux4input_1bit U3(in0[3], in1[3], in2[3], in3[3], out[3], select);
Mux4input_1bit U4(in0[4], in1[4], in2[4], in3[4], out[4], select);
Mux4input_1bit U5(in0[5], in1[5], in2[5], in3[5], out[5], select);
Mux4input_1bit U6(in0[6], in1[6], in2[6], in3[6], out[6], select);
Mux4input_1bit U7(in0[7], in1[7], in2[7], in3[7], out[7], select);

endmodule


module Mux16input_8bit(in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15, out, select);

input [7:0] in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, in12, in13, in14, in15;
output [7:0] out;
input [3:0] select;
wire [7:0] t1, t2, t3, t4;

Mux4input_8bit C1(in0, in1, in2, in3, t1, select[1:0]);
Mux4input_8bit C2(in4, in5, in6, in7, t2, select[1:0]);
Mux4input_8bit C3(in8, in9, in10, in11, t3, select[1:0]);
Mux4input_8bit C4(in12, in13, in14, in15, t4, select[1:0]);
Mux4input_8bit C5(t1, t2, t3, t4, out, select[3:2]);


endmodule
