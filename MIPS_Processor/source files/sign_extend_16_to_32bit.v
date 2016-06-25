module sign_extend_16_to_32bit(out, in);   

input [15:0] in;
output [31:0] out;
parameter delay = 0;

assign #(delay*1000) out = { {16{in[15]}} , in[15:0]};

endmodule