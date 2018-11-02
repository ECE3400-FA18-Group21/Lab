`define SCREEN_WIDTH 176
`define SCREEN_HEIGHT 144
`define NUM_BARS 3
`define BAR_HEIGHT 48

module IMAGE_PROCESSOR (
	PIXEL_IN,
	CLK,
	VGA_PIXEL_X,
	VGA_PIXEL_Y,
	VGA_VSYNC_NEG,
	RESULT
);


//=======================================================
//  PORT declarations
//=======================================================
input	[7:0]	PIXEL_IN;
input 		CLK;

input [9:0] VGA_PIXEL_X;
input [9:0] VGA_PIXEL_Y;
input			VGA_VSYNC_NEG;

reg [31:0] count;

reg detect1;
reg detect2;

output reg [8:0] RESULT;

always@(posedge CLK) begin
	detect1 = VGA_VSYNC_NEG;
	detect2 = detect1;
	if (!detect1 && detect2) begin
		RESULT[0] <= (count > 12672) ? 1 : 0; //if greater than half pixels red
	end
end


always@(posedge CLK) begin
	if (!detect1 && detect2)
		count = 0;
	else if(PIXEL_IN[7:6] >= PIXEL_IN[1:0])
		count = count + 1;
	else
		count = count;
end


endmodule