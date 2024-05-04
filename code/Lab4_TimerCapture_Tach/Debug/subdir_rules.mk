################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Bump.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/Bump.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Bump.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Clock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CortexM.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/CortexM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CortexM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LaunchPad.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Motor.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/Motor.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Motor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PWM.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/PWM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="PWM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SysTick.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/SysTick.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="SysTick.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TA3InputCapture.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/TA3InputCapture.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TA3InputCapture.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TExaS.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/TExaS.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="TExaS.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART0.obj: C:/Users/ojing/Documents/Work/SC2107\ Microcontr\ Sys\ Des\ and\ Dev/Lab/code/LAB_2107_FINAL/inc/UART0.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include" --include_path="C:/ti/ccs1240/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/ojing/Documents/Work/SC2107 Microcontr Sys Des and Dev/Lab/code/LAB_2107_FINAL/Lab4_TimerCapture_Tach" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="UART0.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


