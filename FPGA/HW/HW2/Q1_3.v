module day_counter_withControlers(clk, year, month, day, hour, minute, second, reset, start, stop);

input clk, reset, start, stop;


output [5:0] year;
output [3:0] month;
output [4:0] day;
output [4:0] hour;
output [5:0] minute;
output [5:0] second;


wire control_clk;

reg flag = 0;

always @(posedge clk)
begin
	if(start)
		flag = 1;
	
end
always @(stop)
begin
	if(stop)
		flag = 0;
end	
assign control_clk = (flag) ? clk : 0;

wire second_out, minute_out, hour_out, day_out, month_out, year_out;


defparam second_counter.max_number = 59;
Pcounter_withReset second_counter(control_clk, second_out , second, reset);

defparam minute_counter.max_number = 59;
Pcounter_withReset minute_counter(second_out, minute_out , minute, reset);

defparam hour_counter.max_number = 23;
Pcounter_withReset hour_counter(minute_out, hour_out , hour, reset);

defparam day_counter.max_number = 30;
Pcounter_withReset day_counter(hour_out, day_out , day, reset);

defparam month_counter.max_number = 12;
Pcounter_withReset month_counter(day_out, month_out , month, reset);

defparam year_counter.max_number = 63;
Pcounter_withReset year_counter(month_out, year_out , year, reset);

always @(posedge clk) begin
$monitor ("%d : %d : %d : %d : %d : %d", year, month, day, hour, minute, second);
end
endmodule
