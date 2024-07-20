`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/03/11 18:41:22
// Design Name: 
// Module Name: pwm_generate
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


module pwm_generate(
input clk,
input rst_n,
input [31:0]fre_set,
input [31:0]wav_set,
output PWM_o
    );
reg [31:0]fre_cnt;
always @(posedge clk)begin
    if(rst_n==1'b0)begin
        fre_cnt <= 32'd0;
    end
    else begin
        if(fre_cnt<fre_set) begin
            fre_cnt <= fre_cnt+1'b1;
        end
        else begin
            fre_cnt<=32'd0;
        end
    end
end
assign PWM_o = (wav_set>fre_cnt)?1:0;
endmodule
