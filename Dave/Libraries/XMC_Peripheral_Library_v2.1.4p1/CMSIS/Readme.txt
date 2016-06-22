==================
== INTRODUCTION ==
==================

This folder contains the Cortex Microcontroller Software Interface Standard (CMSIS) v4.5.0.  
http://www.keil.com/pack/doc/CMSIS/General/html/index.html

==============
== CONTENTS ==
==============
In addition to the standard CMSIS components:
 - CMSIS-CORE
 - CMSIS-DSP
 - CMSIS-RTOS

Infineon provides the following content:
XMC Device CMSIS compliant header files
XMC Device CMSIS compliant startup files
XMC Device CMSIS compliant system initialization files
XMC linker files
XMC Device SVD files

======================
== REVISION HISTORY ==
======================

CMSIS v4.5.0p1 (06-04-2015)
--------------------------------------------
- Linker files: 
  1. Add assertion to prevent that region SRAM_combined overflows no_init section.
  2. Fix size of sections copied during initialization from FLASH to RAM to be multiple of 4. 
     It corrects wrong initialization of first variable in section.
- system_XMC4100.c: 
  1. Use correct macro name XMC4108_Q48x64.
     It corrects compilation problems.
  2. Initialization of g_hrpwm_char_data not done for XMC4108_Q48x64 and XMC4108_F64x64.
- startup_XMC410x.s, startup_XMC4200.s, startup_XMC440x.s, startup_XMC450x.s:
  1. Fix weak definition of Veneers when using ENABLE_CPU_CM_001_WORKAROUND.
     It corrects compilation problems.