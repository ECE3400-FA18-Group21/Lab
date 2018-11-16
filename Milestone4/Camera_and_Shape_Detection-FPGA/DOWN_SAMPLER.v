module DOWN_SAMPLER(
    //Inputs
    reset,
	 pclk,
	 href,
	 vsync,
	 rgb565,
	 
	 //Outputs
	 rgb332,
	 X_ADDR,
	 Y_ADDR,
	 WEN,
	 
	 COLOR
    );
	 
    input             reset, pclk, href, vsync;
	 
	 input      [7:0]  rgb565;
	 
	 output reg [7:0]  rgb332;
	 output reg [14:0] X_ADDR, Y_ADDR;
	 output reg        WEN;
	 
	 output reg [2:0]  COLOR; //1 if red, 2 if blue, 0 otherwise
	 
	 localparam [2:0]  IDLE       = 3'd0,
	                   NEW_FRAME  = 3'd1,
	                   FRAME_IDLE = 3'd2,
	                   READ_BYTE_1= 3'd3,
	                   READ_BYTE_2= 3'd4;
							 
	reg         [2:0]  state, next_state;
	
	
	//Color detection wires/regs
	reg         [15:0] rgb565_raw = 0;
	wire        [4:0]  red;
	wire        [5:0]  green;
	wire        [4:0]  blue;
	
	assign red   = rgb565_raw[15:11];
	assign green = rgb565_raw[10:5];
	assign blue  = rgb565_raw[4:0];
	
	
	reg         [14:0] red_count = 0;
	reg         [14:0] blue_count = 0;
	reg         [14:0] unsure_count = 0;
	
	
	// Combinational WEN Logic
	always @ (*) begin
	  if (state == READ_BYTE_2)
		 WEN <= 1;
	  else 
	    WEN <= 0;
	end
	
	
	always @ (posedge pclk) begin
	  // Sequential RGB Downsampling Logic
	  if (state == READ_BYTE_1) begin
		 rgb332[7:5] <= rgb565[7:5];
		 rgb332[4:2] <= rgb565[2:0];
		 rgb565_raw[15:8]  <= rgb565;
	  end
	  else if (state == READ_BYTE_2) begin
		 rgb332[1:0] <= rgb565[4:3];
		 rgb565_raw[7:0] <= rgb565;
	  end
	  
	  // Address Update Logic (Mealy transitions)
	  if (next_state == NEW_FRAME) begin
	    X_ADDR <= 0;
	    Y_ADDR <= 0;
		 if (red_count > blue_count && red_count > unsure_count) begin
		   COLOR <= 1;
		 end	
		 else if (blue_count > red_count && blue_count > unsure_count) begin
		   COLOR <= 2;
		 end
		 else begin
		   COLOR <= 0;
		 end
		 red_count    <= 0;
		 blue_count   <= 0;
		 unsure_count <= 0;
	  end 
	  else if (state == READ_BYTE_2 && next_state == FRAME_IDLE) begin
	    X_ADDR <= 0;
	    Y_ADDR <= Y_ADDR + 1;
	  end
	  else if (state == READ_BYTE_2 && next_state == READ_BYTE_1) begin
	    X_ADDR <= X_ADDR + 1;	
	  end
	  // Sequential Color Detection Logic
	  if (state == READ_BYTE_2) begin
		 if (red > 5'b01000 && green < 6'b010000 && blue < 5'b01000)
		 	  red_count <= red_count + 1;  // Sees Red
		 else if (red < 5'b01000 && green < 6'b010000 && blue > 5'b10000)
		 	  blue_count <= blue_count + 1;  // Sees Blue
		 else
		     unsure_count <= unsure_count + 1; //Not sure
	  end
	  
     // Sequential State Transition Logic	
	  if (reset) begin
	    state <= FRAME_IDLE;
	  end
	  else begin
	    state <= next_state;
	  end
	end
	
	// Combinational Next State Logic
	always @ (*) begin
	  case (state)
	    IDLE:
		   if (vsync)
			  next_state <= NEW_FRAME;
			else
		     next_state <= IDLE;
			  
		 NEW_FRAME:
		   next_state <= FRAME_IDLE; //Should not miss href signal
			
		 FRAME_IDLE:
		   if (href)
			  next_state <= READ_BYTE_1; // Double check timing
			else if (vsync)
			  next_state <= NEW_FRAME;
			else
			  next_state <= FRAME_IDLE;
			  
		 READ_BYTE_1:
		   next_state <= READ_BYTE_2; //Transitions every pclk negedge
			
		 READ_BYTE_2:
		   if (href)
			  next_state <= READ_BYTE_1;
			else
			  next_state <= FRAME_IDLE;
	  endcase
	end
	 

endmodule