module Pcounter_withReset_test;

wire [3 : 0] cnt_out1;
wire out1;
reg clk;
reg reset1 = 0;

wire [6 : 0] cnt_out2;
wire out2;

reg reset2 = 0;
defparam component1.max_number = 3;
Pcounter_withReset component1(clk, out1, cnt_out1, reset1);

defparam component2.max_number = 6;
Pcounter_withReset component2(clk, out2, cnt_out2, reset2);

initial begin 
clk = 0;

forever
#40 clk = ~clk;

end

initial begin

reset1 = 0;
reset2 = 0;

#80
reset1 = 1;
#120
reset2 = 1;

#80
reset1 = 0;
#120
reset2 = 0;

#80
reset1 = 1;
#120
reset2 = 1;

end


endmodule
