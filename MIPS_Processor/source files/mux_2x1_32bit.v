module mux_2x1_32bit (out, in_0, in_1, sel);
	
input  [31:0] in_0, in_1;
input   sel;
output [31:0] out;
	
parameter delay = 0;
	
assign #(delay*1000) out = (sel)? in_1 : in_0;
	
endmodule