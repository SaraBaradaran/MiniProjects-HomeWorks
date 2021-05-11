module PWM_detector(clk, pwm_in, high_read, low_read, data_out);

input clk, pwm_in;
input high_read, low_read;

output [15:0] data_out;
reg [15:0] data_out;
reg [15:0] low_count = 0, high_count = 0;

reg last_state = 1'bz;

always @(high_read , low_read) begin

	high_count = 0;
	low_count = 0;

end
always @(posedge clk) begin

	if (low_read == 0 && high_read == 0) begin
	data_out = 16'bz;

	end


	else if (last_state != pwm_in) begin

		if(high_read == 1 && last_state == 1) begin
		
		data_out = high_count;
		last_state = 0;
		high_count = 0;
		end

		else if(low_read == 1 && last_state == 0) begin
	
		data_out = low_count;
		last_state = 1;
		low_count = 0;
		end	

	end


	if (high_read == 1 && pwm_in == 1) begin

		last_state = 1;
		high_count = high_count + 1;

	end
	else if(low_read == 1 && pwm_in == 0) begin

		last_state = 0;
		low_count = low_count + 1;

	end


end
endmodule 