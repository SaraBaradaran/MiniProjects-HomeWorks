module  Add_Sub(x, y, ans, cout, select);

input [7:0] x, y;
input select;
output [7:0] ans;
output cout;
wire [7:0] carry1, carry2, add_ans, sub_ans;



FullAdder C0(x[0], y[0], 0, add_ans[0], carry1[0]);
FullAdder C1(x[1], y[1], carry1[0], add_ans[1], carry1[1]);
FullAdder C2(x[2], y[2], carry1[1], add_ans[2], carry1[2]);
FullAdder C3(x[3], y[3], carry1[2], add_ans[3], carry1[3]);
FullAdder C4(x[4], y[4], carry1[3], add_ans[4], carry1[4]);
FullAdder C5(x[5], y[5], carry1[4], add_ans[5], carry1[5]);
FullAdder C6(x[6], y[6], carry1[5], add_ans[6], carry1[6]);
FullAdder C7(x[7], y[7], carry1[6], add_ans[7], carry1[7]);

FullAdder W0(x[0], ~y[0], 1, sub_ans[0], carry2[0]);
FullAdder W1(x[1], ~y[1], carry2[0], sub_ans[1], carry2[1]);
FullAdder W2(x[2], ~y[2], carry2[1], sub_ans[2], carry2[2]);
FullAdder W3(x[3], ~y[3], carry2[2], sub_ans[3], carry2[3]);
FullAdder W4(x[4], ~y[4], carry2[3], sub_ans[4], carry2[4]);
FullAdder W5(x[5], ~y[5], carry2[4], sub_ans[5], carry2[5]);
FullAdder W6(x[6], ~y[6], carry2[5], sub_ans[6], carry2[6]);
FullAdder W7(x[7], ~y[7], carry2[6], sub_ans[7], carry2[7]);

assign ans = (select == 1) ? add_ans : sub_ans;
assign cout = (select == 1) ? carry1[7] : carry2[7];

endmodule 
