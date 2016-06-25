module ALU_add_4(out, in);

input [7:0] in;
output [7:0] out;

parameter delay = 0;

assign #(delay*1000) out = in + 8'b00000100;

endmodule