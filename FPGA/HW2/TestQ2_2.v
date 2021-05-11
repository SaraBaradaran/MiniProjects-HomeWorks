module PWM_detector_test;

reg clk, pwm_in;
reg high_read, low_read;
wire [15:0] data_out;
PWM_detector component(clk, pwm_in, high_read, low_read, data_out);


initial begin
pwm_in = 0;
repeat(4) begin
#50 pwm_in = 1;
#100 pwm_in = 0;

end

repeat(5) begin
#30 pwm_in = 1;
#20 pwm_in = 0;

end

repeat(5) begin
#60 pwm_in = 1;
#10 pwm_in = 0;

end

end
initial begin

low_read = 0;
high_read = 1;

#300
high_read = 0;
low_read = 1;


#430
high_read = 1;
low_read = 0;


end
initial begin
clk = 0;
forever 
#5 clk = ~clk;
end

endmodule
