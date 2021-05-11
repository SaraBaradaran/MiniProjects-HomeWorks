module PWM_generator(clk, data_in, low_wr, high_wr, pwm_out);

input clk;
input low_wr, high_wr;
input [15:0] data_in;
output pwm_out;
reg pwm_out;
reg [15:0] i = 0;
reg [1:0] x;
reg flag;
reg [15:0] last_data_in = 0;


always @(posedge clk) begin

if (last_data_in != data_in) begin
	i = data_in;
	flag = 0;
end

if (low_wr == 1 && high_wr == 1)
	x = 1;

else if (low_wr == 1)
	x = 2;

else if (high_wr == 1)
	x = 3;


last_data_in = data_in;

if(x == 1) begin

	
		if(flag == 0) begin
		pwm_out = 0;
		
		end
		else begin
		pwm_out = 1;	

		end
		i = i - 1;
	
	if(i == 0) begin
		flag = ~flag;
		i = data_in;
	end

end
else begin

	if (i == 0) begin
		pwm_out = 16'bz;

	end
	else if (x == 2) begin
		pwm_out = 0;
		i = i - 1;
	end
	else if (x == 3) begin
		pwm_out = 1;
		i = i - 1;
	end
	
end

end
endmodule 