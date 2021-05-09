module winner_tb;

reg [9:0] Out_cr;
wire [1:0] Out_wr;
reg clk;

winner u(Out_cr, Out_wr, clk);

initial 
begin

#5
Out_cr = 10'b01_11_10_01_10;//3

#20
Out_cr = 10'b01_11_10_11_10;//2

#20
Out_cr = 10'b10_10_01_11_10;//2

#20
Out_cr = 10'b11_01_10_01_10;//3

#20
Out_cr = 10'b11_01_10_01_01;//1
end

initial 
begin
clk = 0;
forever
#10 clk = ~clk;

end

endmodule 