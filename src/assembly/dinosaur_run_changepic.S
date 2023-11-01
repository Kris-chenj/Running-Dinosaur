.section .text
.globl dinosaur_run_changepic
.type dinosaur_run_changepic, @function
dinosaur_run_changepic:
	addi sp, sp, -4	#apply sp
	sw ra, 0(sp)	#store address
	add t0, x0, x0	#make t0 zero
	add t0, t0, a0	#t0 get the menu
	add t1, x0, x0	#make t1 zero
	add t1, t1, a1	#t1 get the menu1
	add t2, x0, x0	#make t1 zero
	add t2, t2, a2	#t1 get the menu1
	add t3, x0, x0
	li t3, 1		#make t3 to 1

	
	beq t0, t3, target; # if t0 == t3 then target
	li a0, 35	#set argu
	li a1, 55	#set argu
	li a2, 36	#set argu
	li a3, 59	#set argu
	li a4, 0x0000	#set argu
	add x0, x0, x0
	li a0, 35	#set argu
	li a1, 55	#set argu
	li a2, 36	#set argu
	li a3, 59	#set argu
	li a4, 0x0000	#set argu
	call LCD_Fill	#fill
	li a0, 20	#set argu
	li a1, 40	#set argu
	li a2, 39	#set argu
	li a3, 59	#set argu
	add a4, x0, t1	#set argu
	add x0, x0, x0
	li a0, 20	#set argu
	li a1, 40	#set argu
	li a2, 39	#set argu
	li a3, 59	#set argu
	add a4, x0, t1	#set argu
	call LCD_ShowPic	#show
	j exit


target:
	li a0, 35	#set argu
	li a1, 55	#set argu
	li a2, 36	#set argu
	li a3, 59	#set argu
	li a4, 0x0000	#set argu
	add x0, x0, x0
	li a0, 35	#set argu
	li a1, 55	#set argu
	li a2, 36	#set argu
	li a3, 59	#set argu
	li a4, 0x0000	#set argu
	call LCD_Fill	#fill
	li a0, 20	#set argu
	li a1, 40	#set argu
	li a2, 39	#set argu
	li a3, 59	#set argu
	add a4, x0, t2	#set argu
	add x0, x0, x0
	li a0, 20	#set argu
	li a1, 40	#set argu
	li a2, 39	#set argu
	li a3, 59	#set argu
	add a4, x0, t2	#set argu
	call LCD_ShowPic	#show
	j exit
	
exit:	
    lw ra, 0(sp)		#load back
	addi sp, sp, 4
	ret					#return
