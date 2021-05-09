module Add_Sub_TestBench;

reg [7:0] x, y;
wire [7:0] ans;
reg select;
wire cout;

Add_Sub component1(x, y, ans, cout, select);

initial begin

	$monitor("x = %b , y = %b, ans = %b, cout = %b, select = %b",x, y, ans, cout, select);

	#70
	x = 8'b0000_0000;
	y = 8'b0000_0001;
	select = 1'b1;
	#70
	x = 8'b0000_0010;
	y = 8'b0000_0011;
	#70
	x = 8'b0000_0100;
	y = 8'b0000_0101;
	#70
	x = 8'b0000_1110;
	y = 8'b0000_0111;
	select = 1'b0;
	#70
	x = 8'b0010_1000;
	y = 8'b0000_1001;
	#70
	x = 8'b0111_0110;
	y = 8'b0101_0110;
	#70
	x = 8'b1010_1000;
	y = 8'b0000_1001;
	select = 1'b1;

end

endmodule
