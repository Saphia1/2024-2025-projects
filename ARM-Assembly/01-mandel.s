
			B 	main

xstart		DEFW	-400
xstep   	DEFW    10
xend    	DEFW    400

ystart  	DEFW    -265
ystep   	DEFW    10
yend    	DEFW    265


		ALIGN
main	
;; Initialisations
		LDR R1,xstart
		LDR	R2,xstep
		LDR	R3,xend

		LDR R6,ystart
		LDR	R7,ystep
		LDR	R8,yend




		B loopy
decision

;;i=(2*r*i)/256+y
		MUL	R10,R10,R11
		MOV	R10,R10 LSL #1;;multiply by 2
		MOV	R10,R10 ASR #8;;div by 256
		ADD	R10,R10,R6;;add y
	
;;tmp(r)=r2-i2+x
		
		SUB	R11,R5,R9;;subtract from r2
		ADD	R11,R11,R1;;add i2 and x
		
;;r2=r*r/256

		MUL	R5,R11,R11;;r2=r*r
		MOV	R5,R5 ASR #8;;r2=r2/256

;;i2=i*i/256

		MUL	R9,R10,R10;;i2=i*i
		MOV	R9,R9 ASR #8;;i2=i2/256

;;while((r2 + i2) <= 1024 && --it);
;;(r2 + i2)

		ADD	R0,R9,R5
		
;;--it
		SUB	R4,R4,#1;;--it

;;<= 1024
		CMP	R0,#1024;;is i2+r2 less than or equal to 1024?
		BLE	check2
		B	not0;;if not, then print *
check2	CMP	R4,#0;;is "it" still bigger than 0, max iterations not reached?
		BNE	decision
		B	zero;;if not then print 0
		
		


loopy
		CMP	R6,R8;;have we done enough rows?
		BGE	endy;;if so, end the loop

loopx	;;if not, start a new row
		CMP	R1,R3;;have we done enough columns in this row?
		BGE	endx;; if so end this row
		;;if not then add another column
		MOV	R4,#4096
		MOV	R5,#0
		MOV	R9,#0
		MOV	R10,#0
		MOV	R11,#0
			
		B	decision
		
zero

		MOV R0,#32
		SWI 0
		B printed
not0	
	
		MOV R0,#42
		SWI	0
		B printed
printed	

		ADD R1,R1,R2;;incrementing x by adding xstep to xstart


		B	loopx
endx	
		
		LDR R1,xstart
		MOV R0,#10
		SWI	0
;;adding ystep to ystart
		ADD R6,R6,R7

		B	loopy

;;if ystart is still less than yend, then repeat


endy		
		
		SWI	2		; Terminate the program