
module correlation #(parameter N = 8)(First_num, Second_num, Target_num, clk, Correct_gues, Out_cr, reset);

input [N-1:0] First_num, Second_num, Target_num;
input clk, reset; 
output [1:0] Correct_gues;
output [9:0] Out_cr;

reg [3:0] first_correlation, second_correlation; 
reg [1:0] Correct_gues;
reg [9:0] Out_cr = 0;

reg [3:0] ctr = 0;


always@(posedge clk)
begin
	if(reset)
	begin
		Out_cr <= 0;
		Correct_gues <= 0;
		ctr <= 0;
	end
	

	else
	begin
	first_correlation = cal_correlation(First_num, Target_num);
	second_correlation = cal_correlation(Second_num, Target_num);
	
	if(first_correlation == N && second_correlation == N)
		Correct_gues <= 2'b11;

	else if(first_correlation == N)
		Correct_gues <= 2'b01;

	else if(second_correlation == N)
		Correct_gues <= 2'b10;
	else
		Correct_gues <= 2'b00;

	Out_cr[ctr] <= (first_correlation >= second_correlation);
	Out_cr[ctr + 1] <= (first_correlation <= second_correlation);
	
	ctr <= ctr + 2;

	end	
end
 

function [3:0] cal_correlation;
input [N-1:0] num, target_num;
integer i;
begin
	cal_correlation = 0;

	for(i = 0; i < N; i = i + 1)
	begin

		if(num[i] == target_num[i])
			cal_correlation = cal_correlation + 1;
			
	end
end
endfunction 

endmodule 