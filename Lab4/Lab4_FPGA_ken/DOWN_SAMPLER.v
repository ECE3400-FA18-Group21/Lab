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
	 WEN
    );
	 
    input             reset, pclk, href, vsync;
	 
	 input      [7:0]  rgb565;
	 
	 output reg [7:0]  rgb332;
	 output reg [14:0] X_ADDR, Y_ADDR;
	 output reg        WEN;
	 
	 localparam [2:0]  IDLE       = 3'd0,
	                   NEW_FRAME  = 3'd1,
	                   FRAME_IDLE = 3'd2,
	                   READ_BYTE_1= 3'd3,
	                   READ_BYTE_2= 3'd4;
							 
	reg         [2:0]  state, next_state;
	
   // Sequential State Transition Logic	
	always @ (posedge pclk) begin
	  if (reset)
	    state <= IDLE;
	  else
	    state <= next_state;
	end
	
	// Sequential RGB Downsampling Logic
	always @ (posedge pclk) begin
	  if (state == READ_BYTE_1) begin
		 rgb332[7:5] <= rgb565[7:5];
		 rgb332[4:2] <= rgb565[2:0];
	  end
	  else if (state == READ_BYTE_2)
		 rgb332[1:0] <= rgb565[4:3];
	end
	
	// Combinational WEN Logic
	always @ (*) begin
	  if (state == READ_BYTE_2)
		 WEN <= 1;
	  else 
	    WEN <= 0;
	end
	
	// Address Update Logic (Mealy transitions)
	always @ (negedge pclk) begin  //negedge should be after state transition posedge
	  if (next_state == NEW_FRAME) begin
	    X_ADDR <= 0;
	    Y_ADDR <= 0;
	  end 
	  else if (state == READ_BYTE_2 && next_state == FRAME_IDLE) begin
	    X_ADDR <= 0;
	    Y_ADDR <= Y_ADDR + 1;
	  end
	  else if (state == READ_BYTE_2 && next_state == READ_BYTE_1)
	    X_ADDR <= X_ADDR + 1;
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