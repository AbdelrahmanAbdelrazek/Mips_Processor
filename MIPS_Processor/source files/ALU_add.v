module ALU_add(out, in_0, in_1);

input [7:0] in_0, in_1;
output [7:0] out;

parameter delay = 0;

assign #(delay*1000) out = in_0 + in_1;

endmodule