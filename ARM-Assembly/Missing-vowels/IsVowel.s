		B	test_isvowel

tsv_vowel	DEFB	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
;;vow 		DEFB 	"VOWEL\n",0
;;notvow 		DEFB 	"NOT VOWEL\n",0

		ALIGN

test_isvowel
		MOV		R13,#0x10000

		ADRL	R4,tsv_vowel
		MOV		R5,#26
tsv_loop
		LDRB	R6, [R4],#1
		MOV		R0, R6
		SWI		0

		MOV		R0,#32
		SWI		0
		
		MOV		R0,R6
		BL		isVowel
		SWI		4

		MOV		R0,#10
		SWI		0
		SUB		R5,R5,#1
		CMP		R5,#0
		BGT		tsv_loop

		SWI		2


;; isVowel -- test whether character in R0 is a vowel or not
;; R0 <--- character
;; Returns in  R0: 1 if R0 contained a vowel, 0 otherwise

isVowel
;; Insert your code here
		STMFD	SP!,{R4-R7,R14}
		CMP 	R0,#'A'
		BEQ		vowel
		CMP		R0,#'a'
		BEQ		vowel
		CMP		R0,#'E'
		BEQ		vowel
		CMP		R0,#'e'
		BEQ		vowel
		CMP		R0,#'I'
		BEQ		vowel
		CMP		R0,#'i'
		BEQ		vowel
		CMP		R0,#'O'
		BEQ		vowel
		CMP		R0,#'o'
		BEQ		vowel
		CMP		R0,#'U'
		BEQ		vowel
		CMP		R0,#'u'
		BEQ		vowel
		B		notvowel
vowel	
		;;ADRL	R0, vow
		;;SWI	3
		MOV		R0,#1
		;;SWI		4
		MOV 	PC,R14
notvowel
		;;ADRL	R0, notvow
		;;SWI	3
		MOV 	R0,#0
		;;SWI		4
		LDMFD	SP!,{R4-R7,R14}
		MOV 	PC,R14




