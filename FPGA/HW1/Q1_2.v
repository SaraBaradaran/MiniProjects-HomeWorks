module  FullAdder_8bit(x, y, cin, ans, cout);

input [7:0] x, y;
input cin;
output [7:0] ans;
output cout;
wire [6:0] carry;


FullAdder C0(x[0], y[0], cin, ans[0], carry[0]);
FullAdder C1(x[1], y[1], carry[0], ans[1], carry[1]);
FullAdder C2(x[2], y[2], carry[1], ans[2], carry[2]);
FullAdder C3(x[3], y[3], carry[2], ans[3], carry[3]);
FullAdder C4(x[4], y[4], carry[3], ans[4], carry[4]);
FullAdder C5(x[5], y[5], carry[4], ans[5], carry[5]);
FullAdder C6(x[6], y[6], carry[5], ans[6], carry[6]);
FullAdder C7(x[7], y[7], carry[6], ans[7], cout);
 

endmodule 
