module day_counter_test;
reg clk;

wire [4:0] day;
wire [3:0] month;
wire [5:0] second, minute;
wire [4:0] hour;
wire [5:0] year;

day_counter component(clk, year, month, day, hour, minute, second);

initial begin
clk = 0;
forever
#40 clk = ~clk; 

end


endmodule 