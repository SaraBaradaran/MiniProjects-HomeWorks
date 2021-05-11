
module winner(Out_cr, Out_wr, clk);

input [9:0] Out_cr;
output [1:0] Out_wr;
input clk;

reg [3:0] ctr = 0;
reg [1:0] Out_wr;
reg [2:0] f_cr, s_cr;
always@(posedge clk)
begin
	f_cr = 0; s_cr = 0;
	for( ctr = 0; ctr < 10; ctr = ctr + 2)
	begin
		f_cr = (Out_cr[ctr]) ? f_cr + 1 : f_cr;
		s_cr = (Out_cr[ctr + 1]) ? s_cr + 1 : s_cr;
		
	end

	Out_wr[0] <= (f_cr >= s_cr);
	Out_wr[1] <= (f_cr <= s_cr);
	
end
endmodule 