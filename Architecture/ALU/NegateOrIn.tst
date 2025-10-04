// This file is adapted from part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load NegateOrIn.hdl,
output-file NegateOrIn.out,
compare-to NegateOrIn.cmp,
output-list in%B1.8.1 z%D2.1.2 out%B1.8.1;

set in 0,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B01010110,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B10100101,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B10101010,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B01010101,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00000001,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00000010,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00000100,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00001000,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00010000,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B00100000,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B01000000,
set z 0,
eval,
output;

set z 1,
eval,
output;

set in %B10000000,
set z 0,
eval,
output;

set z 1,
eval,
output;
