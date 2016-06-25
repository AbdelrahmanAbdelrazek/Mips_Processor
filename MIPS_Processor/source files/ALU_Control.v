 module ALU_Control (ALU_out, shift, ALUOp, func,shamt);	
	 
output reg [2:0] ALU_out;
output reg [4:0]shift;
	 
input [1:0] ALUOp;
input [5:0] func;
input [4:0] shamt;

parameter delay = 0;  

parameter [5:0]
	add = 6'b100000, // 32
	AND = 6'b100100, // 36
	NOR = 6'b100111, // 39
	OR  = 6'b100101, // 37
	sll = 6'b000000, // 0
	slt = 6'b101010, // 42
	sub = 6'b100010; // 34
	

		
always@(ALUOp or func) begin
	#(delay*1000)
	casex(ALUOp)
		//add instruction
		2'b00: begin
			ALU_out = 000;
		end
		//Subtract instruction
		2'b01: begin
			ALU_out = 001;
		end
		//and instruction
		2'b11: begin
			ALU_out = 010;
		end
		2'b10: begin
		//R-format instructions
			casex(func)
				add: ALU_out = 000;
				sub: ALU_out = 001;
				AND: ALU_out = 010;
				NOR: ALU_out = 011;
				OR: ALU_out = 100;
				sll:begin 
					ALU_out = 101;
					shift = shamt;
					end
				slt: ALU_out = 110;
			endcase
		end
	endcase
end
		
endmodule