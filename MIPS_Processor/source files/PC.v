module pc(address, clk, next_address);
	
input clk ;
input [7:0]next_address;
output reg [7:0]address;

reg is_first_posedge = 1;
parameter delay = 0;

always @(posedge clk) begin
	#(delay*1000)
	if(is_first_posedge) begin
		address <= 8'b00000000;
		is_first_posedge <= 0;
	end else
		address <= next_address;
end	 
endmodule