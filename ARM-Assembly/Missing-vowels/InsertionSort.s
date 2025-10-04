		B	test_insert
;;test cases below
tis_array	DEFW	2,6,4,6,2,1,1,3,2
;;tis_array	DEFW	1,2,3,4,5,6,7,8,9
;tis_array 	DEFW	9,8,7,6,5,4,3,2,1
;;tis_array	DEFW	9,2,1,4,3,6,5,8,7


		ALIGN

test_insert
		ADRL	R0,tis_array
		MOV		R1,#9
		BL		InsertionSort

		MOV		R2,#0
		MOV		R3,#9
		ADRL	R1,tis_array
		B		tis_cond
tis_loop
		LDR		R0, [R1, R2 LSL #2]
		SWI		4
		MOV		R0,#10
		SWI		0
		ADD		R2,R2,#1
tis_cond
		CMP		R2,R3
		BLT		tis_loop

		SWI		2


; InsertionSort -- should sort the array using the Insertion sort algorithm
; R0 -> array, R1 -> number of elems in array
InsertionSort
		STMFD	SP!,{R4-R7,R14}
		MOV 	R2,#1;;put pointer at second item
start
		CMP		R2, R1
		BGE		endoflist

		LDR		R6, [R0, R2, LSL #2];;;R6 = temp
		MOV		R3, R2
back
		SUB		R5, R3, #1
		LDR		R7, [R0, R5, LSL #2]
		CMP		R3, #0
		BLE		swap;;need to put temp in place
		CMP		R7, R6
		BLE		swap
		STR		R7, [R0, R3, LSL #2]
		SUB		R3, R3, #1
		B		back;;repeat

swap
		STR		R6, [R0, R3, LSL #2]
		ADD		R2, R2, #1
		B		start
endoflist
		MOV     R0, R0
		LDMFD	SP!,{R4-R7,R14}
		MOV     PC, R14

