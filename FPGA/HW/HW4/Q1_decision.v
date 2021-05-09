
module decision(Correct_guess, Out_wr, clk, Result);

input [1:0]Correct_guess, Out_wr;
input clk;
output[1:0] Result;
reg[1:0] Result;

always@(posedge clk)
begin
	if(Correct_guess == 1 || Correct_guess == 2 || Correct_guess == 3)
	begin
		Result <= Correct_guess;
				
	end
	else
		Result <= Out_wr;
end

endmodule 