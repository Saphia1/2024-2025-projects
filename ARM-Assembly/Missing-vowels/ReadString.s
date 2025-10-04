		B	test_readstring

trs_prompt	DEFB 	"Enter a string:",0
trs_report	DEFB	"You entered:",0

		ALIGN

test_readstring
		MOV		R13,#0x10000

		ADRL	R0, trs_prompt
		SWI		3

		ADRL	R0,trs_str
		BL		ReadString

		ADRL	R0,trs_report
		SWI		3

		ADRL	R0,trs_str
		SWI		3

		MOV		R0,#10
		SWI		0
		SWI		2



;; ReadString -- read a string from the keyboard until ENTER/RETURN is pressed
;; 
;; R0 address to place string

ReadString
		STMFD	SP!,{R4-R7,R14} 
		MOV 	R4,R0
		MOV		R3,#0		
rsloop	SWI 	1
		SWI 	0
		CMP 	R0,#10;;enter
		BEQ		endread		
		STRB	R0,[R4,R3]
		ADD		R3,R3,#1
		B 		rsloop

		
endread		
		MOV 	R0,R4
		MOV 	R4,#0
		STRB	R4,[R0,R3]
		LDMFD	SP!,{R4-R7,R14}
		MOV 	PC,R14




trs_str	DEFW	0
