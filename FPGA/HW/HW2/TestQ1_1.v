module Pcounter_test;

wire [3 : 0] cnt_out1;
wire out1;
reg clk;

wire [6 : 0] cnt_out2;
wire out2;

defparam component1.max_number = 3;
Pcounter component1(clk, out1, cnt_out1);

defparam component2.max_number = 6;
Pcounter component2(clk, out2, cnt_out2);

initial begin 
clk = 0;

forever
#40 clk = ~clk;

end

endmodule
