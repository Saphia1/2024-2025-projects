// This file is adapted from part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load Inc8.hdl,
output-file Inc8.out,
compare-to Inc8.cmp,
output-list carryIn%B3.1.3 in%B1.8.1 out%B1.8.1 carryOut%B3.1.3;

set carryIn   %B0,
set in %B00000000,
eval,
output;

set in %B11111111,
eval,
output;

set in %B10101010,
eval,
output;

set in %B01101001,
eval,
output;

set in %B01000110,
eval,
output;

set in %B10000000,
eval,
output;

set in %B10000000,
eval,
output;

set carryIn  %B1,
set in %B00000000,
eval,
output;

set in %B11111111,
eval,
output;

set in %B10101010,
eval,
output;

set in %B01101001,
eval,
output;

set in %B01000110,
eval,
output;

set in %B10000000,
eval,
output;

set in %B10000000,
eval,
output;

