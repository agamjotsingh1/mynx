.global _start
.section .text

_start:
    li t1, 0x12345678        
    li t2, 0x0000FFFF        
    li t3, 0x0000000F        
    csrrw a0, mscratch, t1   
    csrrs a1, mscratch, zero 
    csrrs a2, mscratch, t2   
    csrrs a3, mscratch, zero 
    csrrc a4, mscratch, t3   
    csrrs a5, mscratch, zero 
    csrrwi a6, mepc, 11      
    csrrs a7, mepc, zero     
    csrrsi t4, mepc, 16      
    csrrs t5, mepc, zero     
    csrrci t6, mepc, 3       
    csrrs t0, mepc, zero     

end_loop:
    j end_loop               