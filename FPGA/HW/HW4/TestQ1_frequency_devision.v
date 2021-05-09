module frequency_division_tb;

reg clk, Reset;
wire winner_clk;

frequency_division u(clk, Reset, winner_clk);

initial
begin
clk = 0;
Reset = 1;
#100
Reset = 0;
#400
Reset = 1;
#300
Reset = 0;

end
initial begin
forever
#10 clk = ~clk;

end

endmodule
