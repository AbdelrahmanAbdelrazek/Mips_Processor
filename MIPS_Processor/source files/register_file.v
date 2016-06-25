module register_file(	
	clk,				//the clock to trigger write
	read_data_1, 		//data inside register 1
	read_data_2,	    //data inside register 2
	read_register_1,	//address of register 1
	read_register_2,	//address of register 2
	write_register,		//address of the register to be written in
	write_data,			//data to be written
	RegWrite			//coming from control unit to determine wether to write in a register or not
	);			  
//---------------------Input Ports-------------------------
input clk;
input RegWrite;
input [4:0] read_register_1;
input [4:0] read_register_2;
input [4:0] write_register;
input [31:0] write_data;
//---------------------Output Ports------------------------
output [31:0] read_data_1;
output [31:0] read_data_2;	
//---------------------Input Ports Data type---------------
wire clk;
wire RegWrite;
wire [4:0] read_register_1;
wire [4:0] read_register_2;
wire [4:0] write_register;
wire [31:0] write_data;
//---------------------Output Ports Data type--------------
wire [31:0] read_data_1;
wire [31:0] read_data_2;
//---------------------Internal variable Data type---------
reg [31:0] register_file [0:31];
//--------------------Code starts here---------------------
parameter readDelay = 0;
parameter writeDelay = 0;
initial begin
	$readmemh("register_file.list", register_file);
	register_file[0] = 0;
end

assign #(readDelay*1000) read_data_1 = register_file[read_register_1];
assign #(readDelay*1000) read_data_2 = register_file[read_register_2];		


always @(posedge clk) begin
	#(writeDelay*1000)
	if (RegWrite && write_register != 0) begin
		register_file[write_register] = write_data;
		$writememh("register_file.list", register_file);	
	end	
end		  

endmodule