module day_counter_withControlers_test;

reg clk;

wire [5:0] year;
wire [3:0] month;
wire [4:0] day;
wire [4:0] hour;
wire [5:0] minute;
wire [5:0] second;

reg reset, start, stop;

day_counter_withControlers component(clk, year, month, day, hour, minute, second, reset, start, stop);

initial begin

reset = 0;
stop = 0;
start = 0;

#60
reset = 1;
#80
start = 1;
#80
start = 0;

#200
stop = 1;

#80
stop = 0;

#100
start = 1;


end
initial begin
clk = 0;
forever
#40 clk = ~clk;
end
endmodule
