// This file is adapted from part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.

load Add8C.hdl,
output-file Add8C.out,
compare-to Add8C.cmp,
output-list a%B1.8.1 b%B1.8.1 out%B1.8.1 carryIn%B3.1.3 carry%B3.1.3 overflow%B3.1.3;

set carryIn 0,
set a %B00000000,
set b %B00000000,
eval,
output;

set a %B00000000,
set b %B11111111,
eval,
output;

set a %B11111111,
set b %B11111111,
eval,
output;

set a %B10101010,
set b %B01010101,
eval,
output;

set a %B01101001,
set b %B00111100,
eval,
output;

set a %B01000110,
set b %B01001110,
eval,
output;

set carryIn 1,
set a %B00000000,
set b %B00000000,
eval,
output;

set a %B00000000,
set b %B11111111,
eval,
output;

set a %B11111111,
set b %B11111111,
eval,
output;

set a %B10101010,
set b %B01010101,
eval,
output;

set a %B01101001,
set b %B00111100,
eval,
output;

set a %B01000110,
set b %B01001110,
eval,
output;
