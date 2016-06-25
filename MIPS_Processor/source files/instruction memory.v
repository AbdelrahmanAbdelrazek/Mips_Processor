module instruction_memory(
	instruction,	 //the instruction fetched from memory 
	read_address	 //the address of instruction to be fetched (must be multiples of 4)
	);
//---------------------Input Ports-------------------------
input [7:0] read_address;
//---------------------Output Ports------------------------
output [31:0] instruction;	
//---------------------Input Ports Data type---------------
wire [7:0] read_address;
//---------------------Output Ports Data type--------------
wire [31:0] instruction;
//---------------------Internal variable Data type---------
reg [7:0] instruction_memory [0:255];
//--------------------Code starts here---------------------
parameter delay = 0;

initial begin
	$readmemb("instruction_memory.list", instruction_memory);
end	

assign #(delay*1000) instruction = {instruction_memory[read_address],
					instruction_memory[read_address + 1],
					instruction_memory[read_address + 2],
					instruction_memory[read_address + 3]}; 
					
endmodule