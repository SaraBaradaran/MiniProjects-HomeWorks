module decision_tb;


reg [1:0]Correct_guess, Out_wr;
reg clk;
wire[1:0] Result;

decision u(Correct_guess, Out_wr, clk, Result);

initial 
begin

#10
Correct_guess = 2'b00;
Out_wr = 2'b01;
#20
Correct_guess = 2'b00;
Out_wr = 2'b11;
#20
Correct_guess = 2'b01;
Out_wr = 2'b01;
#20
Correct_guess = 2'b11;
Out_wr = 2'b10;
#20
Correct_guess = 2'b10;
Out_wr = 2'b00;
#20
Correct_guess = 2'b00;
Out_wr = 2'b10;
#20
Correct_guess = 2'b00;
Out_wr = 2'b01;

end

initial
begin
clk = 0;
forever
#10 clk = ~clk;

end
endmodule
