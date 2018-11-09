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

output RESULT;

reg [14:0] count;

always @ (posedge VGA_VSYNC_NEG) begin
    if (count > 12672) begin
        RESULT <= 1;  // if more than half of the pixels were "more red than blue", output 1
    end
    else begin
        RESULT = 0;  // otherwise output 0
    end
    count = 0;
end

always @ (posedge CLK) begin
    if (PIXEL_IN[7:6] > PIXEL_IN[1:0]) begin
        count <= count + 1;  // if red bits are greater than blue bits, increase count
    end
end

endmodule