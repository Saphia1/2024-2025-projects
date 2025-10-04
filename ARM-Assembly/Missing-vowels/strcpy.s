		B	test_strcpy

tsc_string	DEFB	"Hello World",0
tsc_dest	DEFB	"###########################",0
tsc_copied	DEFB	"Copied '",0
tsc_to		DEFB	"' to '",0
tsc_eol		DEFB	"'\n",0
		ALIGN

test_strcpy
		MOV		R13,#0x10000

		ADRL	R0,tsc_dest
		ADRL	R1,tsc_string
		BL		strcpy

		ADRL	R0,tsc_copied
		SWI		3

		ADRL	R0,tsc_string
		SWI		3

		ADRL	R0,tsc_to
		SWI		3

		ADRL	R0,tsc_dest
		SWI		3

		ADRL	R0,tsc_eol
		SWI		3

		SWI		2


;; strcpy -- copy the string at R1 to the address at R0
;; R0 <--- destination
;; R1 <--- source

strcpy
;; Insert your code here
		STMFD	SP!,{R4-R7,R14}
		MOV   R3,#0
copyloop 
		LDRB  R4,[R1, R3]
		STRB  R4,[R0, R3]
		ADD	  R3,R3,#1
		CMP   R4,#0;;newline
		BEQ	  endofstring
		B     copyloop


endofstring
		LDMFD	SP!,{R4-R7,R14}    	
		MOV   PC,R14
