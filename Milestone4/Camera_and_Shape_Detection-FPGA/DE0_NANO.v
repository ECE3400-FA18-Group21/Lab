`define SCREEN_WIDTH 176
`define SCREEN_HEIGHT 144

///////* DON'T CHANGE THIS PART *///////
module DE0_NANO(
	CLOCK_50,
	GPIO_0_D,
	GPIO_1_D,
	KEY
);

//=======================================================
//  PARAMETER declarations
//=======================================================
localparam RED = 8'b111_000_00;
localparam GREEN = 8'b000_111_00;
localparam BLUE = 8'b000_000_11;

//=======================================================
//  PORT declarations
//=======================================================

//////////// CLOCK - DON'T NEED TO CHANGE THIS //////////
input 		          		CLOCK_50;

//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
output 		    [33:0]		GPIO_0_D;
//////////// GPIO_0, GPIO_1 connect to GPIO Default //////////
input 		    [33:0]		GPIO_1_D;
input 		     [1:0]		KEY;

///// PIXEL DATA /////
wire [7:0]	pixel_data_RGB332; // Changed from reg to wire by ken

///// READ/WRITE ADDRESS /////
wire [14:0] X_ADDR; // Changed from reg to wire by ken
wire [14:0] Y_ADDR; // Changed from reg to wire by ken
wire [14:0] WRITE_ADDRESS;
reg [14:0] READ_ADDRESS; 

assign WRITE_ADDRESS = X_ADDR + Y_ADDR*(`SCREEN_WIDTH);

///// VGA INPUTS/OUTPUTS /////
wire 			VGA_RESET;
wire [7:0]	VGA_COLOR_IN;
wire [9:0]	VGA_PIXEL_X;
wire [9:0]	VGA_PIXEL_Y;
wire [7:0]	MEM_OUTPUT;
wire			VGA_VSYNC_NEG;
wire			VGA_HSYNC_NEG;
reg			VGA_READ_MEM_EN;

assign GPIO_0_D[5] = VGA_VSYNC_NEG;
assign VGA_RESET = ~KEY[0];

assign GPIO_0_D[33] = CLK_24; //ADDED FOR CAMERA

///// I/O for Img Proc /////
wire [8:0] RESULT;
wire [2:0] COLOR_DETECT;

assign GPIO_0_D[27] = COLOR_DETECT[0];  // one bit output for more red or more blue
assign GPIO_0_D[29] = COLOR_DETECT[1];  // one bit output for more red or more blue
assign GPIO_0_D[31] = COLOR_DETECT[2];  // Shape detection bit


/* WRITE ENABLE */
wire W_EN; // Changed from reg to wire by ken

///////* CREATE ANY LOCAL WIRES YOU NEED FOR YOUR PLL *///////
wire CLK_24, CLK_25, CLK_50;
///////* INSTANTIATE YOUR PLL HERE *///////
PLL21	PLL21_inst (
	.inclk0 ( CLOCK_50 ),
	.c0 ( CLK_24 ),
	.c1 ( CLK_25 ),
	.c2 ( CLK_50 )
	);

///////* M9K Module *///////
Dual_Port_RAM_M9K mem(
	.input_data(pixel_data_RGB332),
	.w_addr(WRITE_ADDRESS),
	.r_addr(READ_ADDRESS),
	.w_en(W_EN),
	.clk_W(CLOCK_50),
	.clk_R(CLK_25), // DO WE NEED TO READ SLOWER THAN WRITE??
	.output_data(MEM_OUTPUT)
);

///////* VGA Module *///////
VGA_DRIVER driver (
	.RESET(VGA_RESET),
	.CLOCK(CLK_25),
	.PIXEL_COLOR_IN(VGA_READ_MEM_EN ? MEM_OUTPUT : BLUE),
	.PIXEL_X(VGA_PIXEL_X),
	.PIXEL_Y(VGA_PIXEL_Y),
	.PIXEL_COLOR_OUT({GPIO_0_D[9],GPIO_0_D[11],GPIO_0_D[13],GPIO_0_D[15],GPIO_0_D[17],GPIO_0_D[19],GPIO_0_D[21],GPIO_0_D[23]}),
   .H_SYNC_NEG(GPIO_0_D[7]),
   .V_SYNC_NEG(VGA_VSYNC_NEG)
);


///////* Down Sampler *///////
DOWN_SAMPLER down(
	.reset(VGA_RESET),
	.pclk(GPIO_1_D[7]),
	.href(GPIO_1_D[5]),
	.vsync(GPIO_1_D[3]),
	.rgb565({GPIO_1_D[23], GPIO_1_D[21], GPIO_1_D[19], GPIO_1_D[17], GPIO_1_D[15], GPIO_1_D[13], GPIO_1_D[11], GPIO_1_D[9]}),
	.rgb332(pixel_data_RGB332),
	.X_ADDR(X_ADDR),
	.Y_ADDR(Y_ADDR),
	.WEN(W_EN),
	.COLOR(COLOR_DETECT)
    );

///////* Image Processor *///////
//IMAGE_PROCESSOR proc(
//	.PIXEL_IN(MEM_OUTPUT),
//	.CLK(CLK_25),
//	.VGA_PIXEL_X(VGA_PIXEL_X),
//	.VGA_PIXEL_Y(VGA_PIXEL_Y),
//	.VGA_VSYNC_NEG(VGA_VSYNC_NEG),
//	.RESULT(COLOR_DETECT)
//);


///////* Update Read Address *///////
always @ (VGA_PIXEL_X, VGA_PIXEL_Y) begin
		READ_ADDRESS = (VGA_PIXEL_X + VGA_PIXEL_Y*`SCREEN_WIDTH);
		if(VGA_PIXEL_X>(`SCREEN_WIDTH-1) || VGA_PIXEL_Y>(`SCREEN_HEIGHT-1))begin
				VGA_READ_MEM_EN = 1'b0;
		end
		else begin
				VGA_READ_MEM_EN = 1'b1;
		end
end

	
endmodule 