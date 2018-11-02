module downsampler(
	reset,
	clk,
	href,
	rgb565,
	rgb332,
	cycle
	);
	
	input clk;  //24 Mhz clock of camera
	input reset;
	input href;
	input [7:0] rgb565;
	output reg [7:0] rgb332;
	
	output reg cycle;

	always@(posedge clk) begin
		if (reset) begin
			cycle <= 0;
			rgb332 <= 0;
		end
		
		if (href) begin
			if (!cycle) begin
				rgb332[7:5] <= rgb565[7:5];
				rgb332[4:2] <= rgb565[2:0];
			end
			else 
				rgb332[1:0] <= rgb565[4:3];
			cycle <= ~cycle;
		end
		else
			cycle <= 0;
	end
	
endmodule
		