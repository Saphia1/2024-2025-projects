		B	test_makeupper

tmu_string	DEFB	"Hello World",0
tmu_becomes	DEFB	"' becomes '",0
tmu_eol		DEFB	"'\n",0
		ALIGN

test_makeupper
		MOV		R13,#0x10000

		MOV		R0,#39
		SWI		0
		ADRL	R0,tmu_string
		SWI		3

		ADRL	R0,tmu_becomes
		SWI		3

		ADRL	R0,tmu_string
		BL		MakeUpper

		ADRL	R0,tmu_string
		SWI		3

		ADRL	R0,tmu_eol
		SWI		3

		SWI		2


;; MakeUpper -- convert the string at R0 to upper case (capital letters) in place
;; MakeUpper
;; R0 string


MakeUpper
		STMFD	SP!,{R4-R7,R14}
;; Insert your code here
;;65<=UPPER<=90
		MOV   R3,#0
continueloop 
		LDRB  R4,[R0, R3]
		CMP   R4,#91
		BGE	  lower
		B     upper
lower   
		SUB   R4,R4,#32
upper		
		STRB  R4,[R0, R3]
		ADD	  R3,R3,#1
		CMP   R4,#0;;newline
		BEQ	  endupperloop
		B     continueloop


endupperloop
		LDMFD	SP!,{R4-R7,R14}
		MOV   PC,R14