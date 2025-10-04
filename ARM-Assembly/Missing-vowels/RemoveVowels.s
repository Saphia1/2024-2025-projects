		B	test_rmvwls

trv_string	DEFB	"HELLO WORLD",0;;need to change ldrb because doesnt get null, moves to next line of address which is becomes
trv_becomes	DEFB	"' becomes '",0
trv_eol		DEFB	"'\n",0

		ALIGN

test_rmvwls
		MOV		R13,#0x10000

		MOV		R0,#39
		SWI		0
		ADRL	R0,trv_string
		SWI		3

		ADRL	R0,trv_becomes
		SWI		3

		ADRL	R0,trv_string
		BL		RemoveVowels

		ADRL	R0,trv_string
		SWI		3

		ADRL	R0,trv_eol
		SWI		3

		SWI		2



		include isVowel.s


;; RemoveVowels -- remove any vowels in the string at R0 using the isVowel subroutine to identify vowels
;; R0 <-- string

RemoveVowels
;; Insert your code here
		STMFD	SP!,{R4-R7,R14} 
		MOV   R2,#0
		MOV   R3,#0
		MOV	  R4,R0
		MOV	  R1,R14

nextletter 	

		LDRB  R0,[R4, R3]

		CMP   R0,#0;;null
		BEQ	  endstring
		BL     isVowel
		CMP   R0,#1
		BEQ	  skipletter
		LDRB  R0,[R4, R3]
		STRB  R0,[R4, R2]
		ADD	  R2,R2,#1
				
skipletter	
		ADD	  R3,R3,#1
		B     nextletter
	
endstring   	
		
		STRB  R0,[R4, R2]	

		MOV   R0,R4
		LDMFD	SP!,{R4-R7,R14}

		MOV   PC,R14

