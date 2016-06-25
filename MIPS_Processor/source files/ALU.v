module ALU(ALU_result, zero_port, data_in_1, data_in_2,shift, ALU_Control);  
		
input [31:0] data_in_1;
input [31:0] data_in_2;	
input [4:0] shift;
input [2:0] ALU_Control; 

output reg [31:0] ALU_result;
output wire zero_port;
parameter delay = 0;

parameter [2:0]
	add = 3'b000,
	sub = 3'b001,
	AND = 3'b010, 
	NOR = 3'b011, 
	OR  = 3'b100, 
	sll = 3'b101, 
	slt = 3'b110;	

always @(data_in_1 , data_in_2 , ALU_Control) begin
	#(delay*1000) 
	case(ALU_Control)
		add:begin
			ALU_result = data_in_1 + data_in_2;
		end
		sub:begin
			ALU_result = data_in_1 - data_in_2;
		end
		AND:begin
			ALU_result = data_in_1 & data_in_2;
		end
		NOR:begin
			ALU_result = ~(data_in_1 | data_in_2);
		end		
		OR:begin
			ALU_result = data_in_1 | data_in_2;	
		end
		sll:begin
			ALU_result = data_in_2 << shift;
		end
		slt:begin
			if (data_in_1 < data_in_2)
				 ALU_result = 1;
			else 
				 ALU_result = 0;
		end		
	endcase								 
end
	
	assign  zero_port = (ALU_result == 0)? 1 : 0;  
		
endmodule 
