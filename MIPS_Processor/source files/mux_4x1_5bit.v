module mux_4x1_5bit (out, in_0, in_1, in_2, in_3, sel);
	
	input  [4:0] in_0, in_1, in_2, in_3;
	input   [1:0] sel;
	output [4:0] out;
	parameter delay = 0;
	
assign #(delay*1000) out =  (sel == 2'b00) ? in_0 :
			(sel == 2'b01) ? in_1 :
			(sel == 2'b10) ? in_2 : in_3 ;
	
endmodule