module Pcounter(clk, out, cnt_out);

input clk;
output out;
parameter max_number = 1;
output [max_number : 0] cnt_out;

reg out = 0;
reg [max_number : 0] cnt_out = 0;


always @(posedge clk) begin

cnt_out <= cnt_out + 1;
out <= 0;
if (cnt_out == max_number) begin

	cnt_out <= 0;
	out <= 1;

end

end
endmodule 