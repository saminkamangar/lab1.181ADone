module display_hex (
	int,
	hex
);

	input [3:0] int;
	output [7:0] hex;
	
	//wire [7:0] hex_out;
	reg    [7:0] hex_out;
	
	always @ (int)
		case (int)
			0: hex_out = 8'b00111111;
			1: hex_out = 8'b00000110;
			2: hex_out = 8'b01011011;
			3: hex_out = 8'b01001111;
			4: hex_out = 8'b01100110;
			5: hex_out = 8'b01101101;
			6: hex_out = 8'b01111101;
			7: hex_out = 8'b00000111;
			8: hex_out = 8'b01111111;
			9: hex_out = 8'b01100111;
			10: hex_out = 8'b01110111;
			11: hex_out = 8'b01111100;
			12: hex_out = 8'b01111001;
			13: hex_out = 8'b01011110;
			14: hex_out = 8'b01001111;
			15: hex_out = 8'b01110001;
			default: hex_out = 8'b00000000;
		endcase


endmodule