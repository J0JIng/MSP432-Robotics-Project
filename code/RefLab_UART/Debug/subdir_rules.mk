################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Clock.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/RefLab_UART" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Clock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART0.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/UART0.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/RefLab_UART" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="UART0.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/RefLab_UART" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --c99 --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


