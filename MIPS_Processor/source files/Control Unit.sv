module ControlUnit(RegDst, Branch, MemRead, MemtoReg, ALUOp, MemWrite, AluSrc, RegWrite, JumpRegister, Jump, opcode,func); 
	
input [5:0] opcode;
input [5:0] func;

output reg Branch, MemRead, MemWrite, AluSrc, RegWrite;
output reg [1:0] ALUOp;
output reg [1:0] RegDst;
output reg [1:0] MemtoReg;
output reg Jump;
output reg JumpRegister; 

parameter delay = 0;

//jump instruction
//addI inst.
//andI inst.
always @(opcode or func) begin
	#(delay*1000)
	casex (opcode)
	//R-format
		6'b000000: begin
					RegDst = 01;
					AluSrc = 0;
					MemtoReg = 00;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b10;
					Jump = 0;
					if (func == 6'b001000)	 //for jr
						JumpRegister= 1;
					else
						JumpRegister= 0;
						
		end
	//addi 	(confirmed)
		6'b001000: begin
					RegDst = 00;
					AluSrc = 1;
					MemtoReg = 00;
					RegWrite =1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b00;
					Jump = 0;
					JumpRegister = 0;
		end		
	//lw
		6'b100011: begin
					RegDst = 00;
					AluSrc = 1;
					MemtoReg = 01;
					RegWrite = 1;
					MemRead = 1;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b00;
					Jump = 0;
					JumpRegister = 0;
		end
	//sw
		6'b101011: begin
					RegDst = 2'bx;
					AluSrc = 1;
					MemtoReg = 2'bxx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 1;
					Branch = 0;
					ALUOp = 2'b00;
					Jump = 0;
					JumpRegister = 0;
		end
	//andi	 (checked)  (inserted feeh aluop >11)
		6'b001100:begin
					RegDst = 00;
					AluSrc = 1;
					MemtoReg = 00;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 0;
					ALUOp = 2'b11;
					Jump = 0;
					JumpRegister =0;
		end
	//beq
		6'b000100: begin
					RegDst = 2'bx;
					AluSrc = 0;
					MemtoReg = 2'bxx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite =0;
					Branch =1;
					ALUOp =2'b01;
					Jump = 0;
					JumpRegister =0;
		end
	//jal
		6'b000011:	begin
					RegDst = 10;
					AluSrc = 1'bx;
					MemtoReg = 10;
					RegWrite = 1;
					MemRead = 0;
					MemWrite = 0;
					Branch = 1'bx;
					ALUOp = 2'bxx;
					Jump = 1;
					JumpRegister =0;
		end
	//j
		6'b000010: begin
					RegDst = 2'bxx;
					AluSrc = 1'bx;
					MemtoReg = 2'bxx;
					RegWrite = 0;
					MemRead = 0;
					MemWrite = 0;
					Branch = 1'bx;
					ALUOp =2'bxx;
					Jump = 1;
					JumpRegister =0;
			end
	endcase
end	

endmodule
	