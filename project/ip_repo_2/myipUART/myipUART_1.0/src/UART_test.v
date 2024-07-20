`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/05/25 22:44:57
// Design Name: 
// Module Name: UART_test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module UART_test(
    input clk,
    input wire rx,
    output reg [7:0]message = 0,
    output reg over=0
);                                                                                                  
    reg [32:0]cnt_clk=0;                                
    reg [4:0]cnt_message=0;                            
    reg [7:0]message_mid=0;                     
    reg r_start=1;                                     
    reg [20:0]cnt = 0;
    always @(posedge clk)
    begin
        if (rx==0&&r_start==1) begin
                cnt_clk<=cnt_clk+1;
                if (cnt_clk==5208&&rx==0) begin
                    r_start<=0;
                    cnt_clk<=0;
                    cnt_message<=0;
                    message_mid<=0;
                end
            end                                            
            else if (r_start==0) begin
                cnt_clk<=cnt_clk+1;
                if (cnt_clk==10416) begin                   
                    message_mid[cnt_message]<=rx;
                    cnt_message<=cnt_message+1;
                    cnt_clk<=0;
                end                                            
                else if (cnt_message==8) begin            
                    if (cnt_clk==8000) begin               
                                                            
                        over<=1;
                        cnt_clk<=0;
                        cnt_message<=0;
                        message_mid<=0;
                        r_start<=1;
                    end
                    if (cnt_clk==5000) begin
                        message<=message_mid;
                        over<=0;
                    end
                end
            end
            else begin
                r_start<=1;
            end
    end

endmodule
