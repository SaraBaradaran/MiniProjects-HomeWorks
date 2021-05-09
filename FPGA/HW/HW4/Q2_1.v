module correlation_32(num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16, Target_Num, clk, Reset, Out_4);


input clk, Reset;
input [31:0] Target_Num,
num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8, num_9, num_10, num_11, num_12, num_13, num_14, num_15, num_16;
output [3:0] Out_4;

reg [4:0] i;
reg [5:0] corr [1:16];
reg [5:0] max_corr;
reg [4:0] max_num;
always@(posedge clk)
begin
	if(Reset)
	begin
		for(i = 1; i < 16; i = i + 1)
			corr[i] = 0;
		max_num = 5'bz;
	end
	else
	begin
		corr[1] = cal_correlation(num_1, Target_Num);
		corr[2] = cal_correlation(num_2, Target_Num);
		corr[3] = cal_correlation(num_3, Target_Num);
		corr[4] = cal_correlation(num_4, Target_Num);
		corr[5] = cal_correlation(num_5, Target_Num);
		corr[6] = cal_correlation(num_6, Target_Num);
		corr[7] = cal_correlation(num_7, Target_Num);
		corr[8] = cal_correlation(num_8, Target_Num);
		corr[9] = cal_correlation(num_9, Target_Num);

		corr[10] = cal_correlation(num_10, Target_Num);
		corr[11] = cal_correlation(num_11, Target_Num);
		corr[12] = cal_correlation(num_12, Target_Num);
		corr[13] = cal_correlation(num_13, Target_Num);
		corr[14] = cal_correlation(num_14, Target_Num);
		corr[15] = cal_correlation(num_15, Target_Num);
		corr[16] = cal_correlation(num_16, Target_Num);
	
		max_corr = 0;
		max_num = 1;
		for (i = 1; i <= 16; i = i + 1)
		begin
			if(max_corr < corr[i])
			begin
				max_corr = corr[i];
				max_num = i;			end
		end
	end
end

assign Out_4 = max_num - 1;

function [5:0] cal_correlation;
input [31:0] num, target_num;
integer i;
begin
	cal_correlation = 0;

	for(i = 0; i < 32; i = i + 1)
	begin

		if(num[i] == target_num[i])
			cal_correlation = cal_correlation + 1;
			
	end
end
endfunction 


endmodule 
