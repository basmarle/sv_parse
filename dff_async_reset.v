// http://www.asic-world.com/code/hdl_models/dff_async_reset.v
//-----------------------------------------------------
// Design Name : dff_async_reset
// File Name   : dff_async_reset.v
// Function    : D flip-flop async reset
// Coder       : Deepak Kumar Tala
//-----------------------------------------------------
module level2();
endmodule

module level1();
level2 level2_i();
endmodule

module main(input logic a, input logic b);

level1 level1_i();
wire baas;
initial begin
baas <= 1;
end
endmodule