module sll_2_8bit(out, in); 
	
input [5:0] in;
output [7:0] out;
parameter delay = 0;

assign #(delay*1000) out = {in, 2'b00};

endmodule

	