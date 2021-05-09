module FullAdder(x, y, cin, ans, cout);
input x, y, cin;
output ans, cout;
reg ans, cout;

always @(x, y, cin) begin

 ans = x + y + cin;
 cout = (x + y + cin) / 2;

end
endmodule 