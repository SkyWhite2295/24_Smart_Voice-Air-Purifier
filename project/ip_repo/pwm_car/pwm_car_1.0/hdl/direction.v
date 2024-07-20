`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/03/12 13:57:27
// Design Name: 
// Module Name: direction
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


`timescale 1ns / 1ps
module direction(clk,
                mode,
                dir_out1,
                dir_out2);
input clk;
input[1:0] mode;
output dir_out1;
output dir_out2;
reg dir_out1;
reg dir_out2;

always@(posedge clk)
    {dir_out1,dir_out2} = mode;
    
endmodule
