module Pcounter_withReset(clk, out, cnt_out, reset);

input clk, reset;
output out;
parameter max_number = 1;
output [max_number : 0] cnt_out;

reg out = 0;
reg [max_number : 0] cnt_out = 0;

always @(reset) begin

if(reset == 0)
	cnt_out <= 0;

end


always @(posedge clk) begin
if (reset == 0)
	cnt_out <= 0;
else 
	cnt_out <= cnt_out + 1;

out <= 0;
if (cnt_out == max_number) begin

	cnt_out <= 0;
	out <= 1;

end

end
endmodule 
