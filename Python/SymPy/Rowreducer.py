def rref_ops(A):
    ops =[];#array to store operations
    pivrow=0;#current row with pivot in it index
    A=A.copy()
    columns=A.shape[1]
    rows=A.shape[0]
    for col in range (0, columns):
        swap = None#row to swap with
        #find pivrow for current col
        for row in range (pivrow, rows):
            #Swap the 1st row with a lower one so a leftmost nonzero entry is in the 1st row (if necessary).
            
            if A[row, col]!=0:
                swap=row#set as row we need to swap
                break
                
        if swap is None:#no piv found
            continue

        if swap != pivrow:#need to swap to bring pivot to top  
            ops.append(("swap",pivrow,swap))
            A=A.elementary_row_op("n<->m",row1=pivrow,row2=swap)#swap
                    
        # Scale the 1st row so that its first nonzero entry is equal to 1.
        if A[pivrow, col] != 1:#is scaling needed
            #pivrow=row
            c=Rational(1,A[pivrow, col])#scalar calculation
            ops.append(("scale", pivrow, c ))
            A=A.elementary_row_op("n->kn",row=pivrow,k=c)
                
    
        #Use row replacement so all entries below this 1 are 0.
        for row in range (pivrow+1,rows):
            if A[row, col] != 0:
                f= -A[row, col]#factor to add
                ops.append(("replace",row,f,pivrow))
                A=A.elementary_row_op("n->n+km",row=row,row2=pivrow,k=f)
        
        if swap is not None:
            pivrow+=1#increment
        
    #clear up
    for col in range (columns-1,-1,-1):#last col moving left
        for row in range (rows-1,-1,-1):#bottom upwards
                if A[row, col]==1: 
                    for uprow in range(row):#remove non zeros above pivot
                        if A[uprow, col]!=0:
                            f =-A[uprow, col]
                            ops.append(("replace",uprow,f,row))
                            A = A.elementary_row_op("n->n+km",row=uprow,row2=row,k=f)
                    break#stop moving through column

    
    return ops#, A

#A = Matrix ([[0, 1], [2, 1]])


#rref_array=rref_ops(A)#, rref_A
#print(rref_array)#, rref_A)