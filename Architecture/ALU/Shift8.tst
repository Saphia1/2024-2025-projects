// This file is adapted from part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load Shift8.hdl,
output-file Shift8.out,
compare-to Shift8.cmp,
output-list in%B1.8.1 out%B1.8.1 carryOut%B3.1.3;

set in %B00000000,
eval,
output;

set in %B11111111,
eval,
output;

set in %B10000000,
eval,
output;

set in %B01000000,
eval,
output;

set in %B00100000,
eval,
output;

set in %B00010000,
eval,
output;

set in %B00001000,
eval,
output;

set in %B00000100,
eval,
output;

set in %B00000010,
eval,
output;

set in %B00000001,
eval,
output;

set in %B11000000,
eval,
output;

set in %B01100000,
eval,
output;

set in %B00110000,
eval,
output;

set in %B00011000,
eval,
output;

set in %B00001100,
eval,
output;

set in %B00000110,
eval,
output;

set in %B00000011,
eval,
output;

set in %B10000001,
eval,
output;


