module zero_extend_8_to_32bit(out, in);   

input [7:0] in;
output [31:0] out;

parameter delay = 0;

assign #(delay*1000) out = { 24'b0, in[7:0]};

endmodule