module FullAdder_8bit_TestBench;

reg [7:0] x, y;
reg cin;
wire cout;
wire [7:0] ans;

FullAdder_8bit component1(x, y, cin, ans, cout);

initial begin

	$monitor ("x = %b, y = %b, cin = %b, cout = %b, ans = %b", x, y, cin, cout, ans);
	#70
	x = 8'b0000_0000;
	y = 8'b0000_0001;
	cin = 1'b1;
	#70
	x = 8'b0000_0010;
	y = 8'b0000_0011;
	cin = 1'b0;
	#70
	x = 8'b0000_0100;
	y = 8'b0000_0101;
	cin = 1'b1;
	#70
	x = 8'b0000_0110;
	y = 8'b0000_0111;
	cin = 1'b0;
	#70
	x = 8'b0000_1000;
	y = 8'b0000_1001;
	cin = 1'b1;
	#70
	x = 8'b0001_0000;
	y = 8'b0100_0111;
	cin = 1'b0;
	#70
	x = 8'b1010_1000;
	y = 8'b1000_1001;
	cin = 1'b1;
	#70
	x = 8'b0010_0110;
	y = 8'b1001_1111;
	cin = 1'b0;
	#70
	x = 8'b1110_1000;
	y = 8'b1000_1001;
	cin = 1'b1;
end
endmodule
