module FullAdder_TestBench;

reg x, y, cin;
wire ans, cout;

FullAdder Component1(x, y, cin, ans, cout);
initial begin
	$monitor ("x = %b, y = %b, cin = %b, carry = %b, ans = %b", x, y, cin, cout, ans);
	#20
	x = 1'b0;
	y = 1'b0;
	cin = 1'b0;
	#20
	x = 1'b1;
	y = 1'b0;
	cin = 1'b0;
	#20
	x = 1'b0;
	y = 1'b1;
	cin = 1'b0;
	#20
	x = 1'b1;
	y = 1'b1;
	cin = 1'b0;
	#20
	x = 1'b0;
	y = 1'b0;
	cin = 1'b1;
	#20
	x = 1'b1;
	y = 1'b0;
	cin = 1'b1;
	#20
	x = 1'b0;
	y = 1'b1;
	cin = 1'b1;
	#20
	x = 1'b1;
	y = 1'b1;
	cin = 1'b1;
end
endmodule 

