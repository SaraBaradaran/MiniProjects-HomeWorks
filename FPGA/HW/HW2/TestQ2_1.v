module PWM_generator_test;

reg low_wr, high_wr;
reg [15:0] data_in;
wire pwm_out;
reg clk;
PWM_generator component(clk, data_in, low_wr, high_wr, pwm_out);

initial begin

data_in = 5;
low_wr = 1;
high_wr = 1;

#410
data_in = 2;

#240
data_in = 1;


#80
low_wr = 1;
high_wr = 0;
data_in = 3;
forever begin

#60
low_wr = 0;
high_wr = 1;
data_in = 5;
#100
low_wr = 1;
high_wr = 0;
data_in = 3;
end


end 

initial begin
clk = 0;
forever
#10 clk = ~clk;


end


endmodule
