		B	test_cwrdl

tcwrdl_string	DEFB	"THE CAT SAT ON THE MAT",0

		ALIGN

test_cwrdl
		MOV		R13,#0x10000

		ADRL	R0,tcwrdl_string
		SWI		3

		ADRL	R0,tcwrdl_string
		ADRL	R1,tcwrdl_array
		BL		CountWordLengths
		MOV		R3,R0
		MOV		R0,#10
		SWI		0

		MOV		R2,#0
		ADRL	R1,tcwrdl_array
		B		tcwrdl_cond
tcwrdl_loop
		LDR		R0, [R1, R2 LSL #2]
		SWI		4
		MOV		R0,#10
		SWI		0
		ADD		R2,R2,#1
tcwrdl_cond
		CMP		R2,R3
		BLT		tcwrdl_loop

		SWI		2


;; CountWordLengths -- fill in an array with the length of each word in the string
;; R0 <-- string
;; R1 <-- array to file
;; Returns: The number of words found in R0.

CountWordLengths
;; Insert your code here
		STMFD	SP!,{R4-R7,R14}
		MOV   R2,#0;;word total
		MOV	  R3,#0;;letters
		MOV	  R4,R0
		;;MOV   R5,R14


getnextletter	
		LDRB  R0,[R4],#1
		CMP   R0,#0;;null
		BEQ	  newword
		CMP   R0,#32;;space
		BEQ	  newword
		ADD	  R3,R3,#1

		B 	  getnextletter
			
newword	
		CMP   R3,#0
		BEQ   emptyword
		STR  R3,[R1,R2 LSL #2]
		ADD	  R2,R2,#1
emptyword		
		MOV   R3,#0
		CMP   R0,#0
		BEQ	  endword
		B     getnextletter
	
endword   	
		MOV   R0,R2
		LDMFD	SP!,{R4-R7,R14}
		MOV   PC,R14





;; DO NOT REMOVE THIS LABEL
tcwrdl_array	DEFW	0	
