module day_counter(clk, year, month, day, hour, minute, second);

input clk;

output [4:0] day;
output [3:0] month;
output [5:0] second, minute;
output [4:0] hour;
output [5:0] year;

wire second_out, minute_out, hour_out, day_out, month_out, year_out;

defparam second_counter.max_number = 59;
Pcounter second_counter(clk, second_out , second);

defparam minute_counter.max_number = 59;
Pcounter minute_counter(second_out, minute_out , minute);

defparam hour_counter.max_number = 23;
Pcounter hour_counter(minute_out, hour_out , hour);

defparam day_counter.max_number = 30;
Pcounter day_counter(hour_out, day_out , day);

defparam month_counter.max_number = 12;
Pcounter month_counter(day_out, month_out , month);

defparam year_counter.max_number = 63;
Pcounter year_counter(month_out, year_out , year);


always @(posedge clk) begin
$monitor ("%d : %d : %d : %d : %d : %d", year, month, day, hour, minute, second);
end
endmodule
