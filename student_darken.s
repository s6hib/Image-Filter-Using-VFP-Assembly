.global sdarken
sdarken:
    PUSH {LR}
    PUSH {R4-R12}

	MULS R4, R2, R3
    BLE end
    ADD R5, R0, R4
    ADD R6, R5, R4
    ADD R7, R1, R4
    ADD R8, R7, R4
    MOV R9, #0

    // Enable VFP
    VMRS R12, fpscr
    ORR R12, R12, #0x40000000
    VMSR fpscr, R12

loop:
    LDRB R10, [R0, R9]
    LDRB R11, [R5, R9]
    LDRB R12, [R6, R9]

    // Convert R10 and R11 to floating point and store them in d0 and d1
    VMOV S0, R10
    VMOV S1, R11
    VCVT.F32.U32 S0, S0
    VCVT.F32.U32 S1, S1

    // Calculate the ratio of red to green channel values, store the result in S2
    VDIV.F32 S2, S0, S1

    // Load the threshold value into S3
    VMOV S3, #1.5

    // Compare S2 and S3
    VCMP.F32 S2, S3

    // Update APSR_nzcv flags
    VMRS APSR_nzcv, FPSCR

    // If the ratio is greater than the threshold, apply the filter
    BGT apply_filter
    B continue

apply_filter:
	// Enhance the blue channel intensity proportionally to the red-to-green ratio
    VMOV S4, R12
    VCVT.F32.U32 S4, S4
    VMUL.F32 S4, S4, S2
    VCVT.U32.F32 S4, S4
    VMOV R12, S4

continue:
    STRB R10, [R1, R9]
    STRB R11, [R7, R9]
    STRB R12, [R8, R9]

    ADD R9, R9, #1
    CMP R9, R4
    BLT loop

end:
    // Disable VFP
    VMRS R12, fpscr
    BIC R12, R12, #0x40000000
    VMSR fpscr, R12

	POP {R4-R12}
    POP {PC}
