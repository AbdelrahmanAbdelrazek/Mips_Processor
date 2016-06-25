module MIPS_processor;
	reg clk;
	wire [7:0] address, next_address, shifted_extended_signal, current_address_plus_4, branch_address, jump_address, ALU_add_result, branch_jump_address; 					   
	wire [31:0] instruction, read_data_1, read_data_2, write_data, extended_signal, ALU_2nd_input, ALU_result, read_data, current_address_plus_4_32bit;
	wire [1:0]  RegDst, ALUOp, MemtoReg; 
	wire [4:0]  write_register, shift;
	wire [2:0]  ALU_Control;  
	wire 	    Branch, MemRead, MemWrite, AluSrc, RegWrite, Jump, JumpRegister, zero_port;
	parameter register_31 = 5'b11111;	  
	
//-------------------------Clock Generation--------------------------------- 
	initial begin 
		clk = 1;
	end
	always begin
		#(25*1000) clk = ~clk;	  //clock cycle = 50ns
	end				  
	
//-------------------------Structural Model---------------------------------
	pc #5 pc1(address, clk, next_address);	

	ALU_add_4 #1 ALU1(current_address_plus_4, address);
	
	instruction_memory #7 inst_mem(instruction, address);
	
	register_file #(3,4) reg_file(clk, read_data_1, read_data_2, instruction[25:21], instruction[20:16], write_register, write_data, RegWrite); //writeDelay must be < 5 and perfably be greeter than readDelay
	
	mux_4x1_5bit #1 mux_reg(write_register, instruction[20:16], instruction[15:11], register_31, 5'bz, RegDst);		//we will never use pin 3 of the mux so we connect it as high impedance  
	
	ControlUnit #2 contro1(RegDst, Branch, MemRead, MemtoReg, ALUOp, MemWrite, AluSrc, RegWrite, JumpRegister, Jump, instruction[31:26], instruction[5:0]);
	
	mux_2x1_32bit #1 mux_alu(ALU_2nd_input, read_data_2, extended_signal,AluSrc);
	
	ALU #5 main_ALU(ALU_result, zero_port, read_data_1, ALU_2nd_input, shift, ALU_Control); 
	
	ALU_Control #3 ALU_co(ALU_Control , shift, ALUOp ,instruction[5:0], instruction[10:6]);
	
	sign_extend_16_to_32bit #2 sign_ext_16_to_32(extended_signal, instruction[15:0]);
	
	data_memory #(5,6) data_mem(read_data, clk, ALU_result, read_data_2, MemWrite, MemRead);  //readDelay must be < 10
	
	zero_extend_8_to_32bit zero_ex_8_32bit(current_address_plus_4_32bit, current_address_plus_4);
																								  
	mux_4x1_32bit #1 mux_mem(write_data, ALU_result, read_data, current_address_plus_4_32bit, 32'bz, MemtoReg);	
	
	sll_2_8bit #1 sll_2_branch(shifted_extended_signal, extended_signal[7:0]);
	
	ALU_add #2 ALU_add_branch(ALU_add_result, current_address_plus_4, shifted_extended_signal);
	
	and #1(branch_if_equal, Branch, zero_port);
	
	sll_2_8bit #1 sll_2_jump(jump_address, instruction[5:0]);
	
	mux_2x1_8bit #1 mux_branch(branch_address, current_address_plus_4, ALU_add_result, branch_if_equal);
	
	mux_2x1_8bit #1 mux_jump(branch_jump_address, branch_address, jump_address, Jump);
	
	mux_2x1_8bit #1 mux_jump_register(next_address, branch_jump_address, read_data_1[7:0], JumpRegister);

	
endmodule