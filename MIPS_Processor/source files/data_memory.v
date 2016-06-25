module data_memory(	
	read_data, 			//data inside memory cell to be read			
	clk,				//the clock to trigger write  
	address,			//address of memory cell to be read	  (must be multiples of 4)
	write_data,			//data to be written
	MemWrite,			//coming from control unit to determine wether to write in the memory or not 
	MemRead,			//coming from control unit to determine wether to read from memory or not
	);			  
//---------------------Input Ports-------------------------
input clk;
input MemWrite;
input MemRead;
input [31:0] address;
input [31:0] write_data;
//---------------------Output Ports------------------------
output [31:0] read_data;	
//---------------------Input Ports Data type---------------
wire clk;
wire MemWrite;
wire MemRead;
wire [31:0] address;
wire [31:0] write_data;
//---------------------Output Ports Data type--------------
wire [31:0] read_data;
//---------------------Internal variable Data type---------
reg [7:0] data_memory [0:2047];
//--------------------Code starts here---------------------
parameter readDelay= 0;
parameter writeDelay= 0;


initial begin 						 
	$readmemh("data_memory.list", data_memory);
end

assign #(readDelay*1000) read_data = (MemRead)? {data_memory[address[10:0]],
								data_memory[address[10:0] + 1],
								data_memory[address[10:0] + 2],
								data_memory[address[10:0] + 3]} : read_data;


always @(posedge clk) begin	
	if (MemWrite) begin
		#(writeDelay*1000)
		{data_memory[address[10:0]],
		data_memory[address[10:0] + 1],
		data_memory[address[10:0] + 2],
		data_memory[address[10:0] + 3]} = write_data;
		$writememh("data_memory.list", data_memory);	
	end	
end		  

endmodule