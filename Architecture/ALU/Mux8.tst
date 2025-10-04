// This file is adapted from part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load Mux8.hdl,
output-file Mux8.out,
compare-to Mux8.cmp,
output-list a%B1.8.1 b%B1.8.1 sel%D2.1.2 out%B1.8.1;

set a 0,
set b 0,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set a %B00000000,
set b %B01010110,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set a %B10100101,
set b %B00000000,
set sel 0,
eval,
output;

set sel 1,
eval,
output;

set a %B10101010,
set b %B01010101,
set sel 0,
eval,
output;

set sel 1,
eval,
output;
