module frequency_division(clk, Reset, winner_clk);

input clk, Reset;
output winner_clk;
reg [2:0] counter = 0;
reg winner_clk = 0;
always@(posedge clk or negedge clk)
begin

	if(Reset)
		counter <= 0;
	
	else if(clk == 1)
	begin
		if(counter < 4)
			counter <= counter + 1;
		else
		begin
			counter <= 0;
			if(winner_clk)
				winner_clk <= 0;
			else
				winner_clk <= 1;
		end
	end
	else if(clk == 0)
	begin
		if(counter < 4)
			counter <= counter + 1;
		else
		begin
			counter <= 0;
			if(winner_clk)
				winner_clk <= 0;
			else
				winner_clk <= 1;
		end
	end
end


endmodule
