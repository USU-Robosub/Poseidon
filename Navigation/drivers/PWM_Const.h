/*
 * PWM_Const.h
 *
 *  Created on: Jan 22, 2015
 *      Author: TekuConcept
 */

#ifndef PWM_CONST_H_
#define PWM_CONST_H_


// Subsystem
#define PWM_SUB0            0x48300000 // Section 2.1           (Pg  161)
#define PWM_SUB1            0x48302000 // Section 2.1           (Pg  162)
#define PWM_SUB2            0x48304000 // Section 2.1

// Specific
#define PWM_IDVER           0x00000000 // Section 15.1.3        (Pg 1489)   IP Revision
#define PWM_SYSCONFIG       0x00000004 // Section 15.1.3                System Configuration
#define PWM_CLKCONFIG       0x00000008 // Section 15.1.3                Clock Configuration
#define PWM_CLKSTATUS       0x0000000C // Section 15.1.3                Clock Status

// eCAP
#define PWM_TSCTR           0x00000100 // Section 15.3.4.1      (Pg 1634)   Time-Stamp Counter
#define PWM_CTRPHS          0x00000104 // Section 15.3.4.1              Counter Phase Offset Value
#define PWM_CAP1            0x00000108 // Section 15.3.4.1              Capture 1
#define PWM_CAP2            0x0000010C // Section 15.3.4.1              Capture 2
#define PWM_CAP3            0x00000110 // Section 15.3.4.1              Capture 3
#define PWM_CAP4            0x00000114 // Section 15.3.4.1              Capture 4
#define PWM_ECCTL1          0x00000128 // Section 15.3.4.1              Capture Control 1
#define PWM_ECCTL2          0x0000012A // Section 15.3.4.1              Capture Control 2
#define PWM_ECEINT          0x0000012C // Section 15.3.4.1              Capture Interrupt Enable
#define PWM_ECFLG           0x0000012E // Section 15.3.4.1              Capture Interrupt Flag
#define PWM_ECCLR           0x00000130 // Section 15.3.4.1              Capture Interrupt Clear
#define PWM_ECFRC           0x00000132 // Section 15.3.4.1              Capture Interrupt Force
#define PWM_eCAP_REVID      0x0000015C // Section 15.3.4.1              Revision ID

// eQEP
#define PWM_QPOSCNT         0x00000180 // Section 15.4.3        (Pg 1672)   Position Counter
#define PWM_QPOSINIT        0x00000184 // Section 15.4.3                Position Counter Initialization
#define PWM_QPOSMAX         0x00000188 // Section 15.4.3                Maximum Position Count
#define PWM_QPOSCMP         0x0000018C // Section 15.4.3                Position-Compare
#define PWM_QPOSILAT        0x00000190 // Section 15.4.3                Index Position Latch
#define PWM_QPOSSLAT        0x00000194 // Section 15.4.3                Strobe Position Latch
#define PWM_APOSLAT         0x00000198 // Section 15.4.3                Position Counter Latch
#define PWM_QUTMR           0x0000019C // Section 15.4.3                Unit Timer
#define PWM_QUPRD           0x000001A0 // Section 15.4.3                Unit Period
#define PWM_QWDTMR          0x000001A4 // Section 15.4.3                Watchdog Timer
#define PWM_QWDPRD          0x000001A6 // Section 15.4.3                Watchdog Period
#define PWM_QDECCTL         0x000001A8 // Section 15.4.3                Decoder Control
#define PWM_QEPCTL          0x000001AA // Section 15.4.3                Control
#define PWM_QCAPCTL         0x000001AC // Section 15.4.3                Capture Control
#define PWM_QPOSCTL         0x000001AE // Section 15.4.3                Position-Compare Control
#define PWM_QEINT           0x000001B0 // Section 15.4.3                Interrupt Enable
#define PWM_QFLG            0x000001B2 // Section 15.4.3                Interrupt Flag
#define PWM_QCLR            0x000001B4 // Section 15.4.3                Interrupt Clear
#define PWM_QFRC            0x000001B6 // Section 15.4.3                Interrupt Force
#define PWM_QEPSTS          0x000001B8 // Section 15.4.3                Status
#define PWM_QCTMR           0x000001BA // Section 15.4.3                Capture Timer
#define PWM_QCPRD           0x000001BC // Section 15.4.3                Capture Period
#define PWM_QCTMRLAT        0x000001BE // Section 15.4.3                Capture Timer Latch
#define PWM_QCPRDLAT        0x000001C0 // Section 15.4.3                Capture Period Latch
#define PWM_eQEP_REVID      0x000001DC // Section 15.4.3                Revision ID

// ePWM
// -----    Time-Based          -----
#define PWM_TBCTL           0x00000200 // Section 15.2.4        (Pg 1581)   Time-Base Control
#define PWM_TBSTS           0x00000202 // Section 15.2.4                Time-Base Status
#define PWM_TBPHSHR         0x00000204 // Section 15.2.4                Extension for HRPWM Phase
#define PWM_TBPHS           0x00000206 // Section 15.2.4                Time-Base Phase
#define PWM_TBCNT           0x00000208 // Section 15.2.4                Time-Base Counter
#define PWM_TBPRD           0x0000020A // Section 15.2.4                Time-Base Period
// -----    Counter-Compare     -----
#define PWM_CMPCTL          0x0000020E // Section 15.2.4                Counter-Compare Control
#define PWM_CMPAHR          0x00000210 // Section 15.2.4                Extension for HRPWM Counter Compare A
#define PWM_CMPA            0x00000212 // Section 15.2.4                Counter-Compare A
#define PWM_CMPB            0x00000214 // Section 15.2.4                Counter-Compare B
// -----    Action-Qualifier    -----
#define PWM_AQCTLA          0x00000216 // Section 15.2.4                Action-Qualifier Control for Output A (ePWMxA)
#define PWM_AQCTLB          0x00000218 // Section 15.2.4                Action-Qualifier Control for Output B (ePWMxB)
#define PWM_AQSFRC          0x0000021A // Section 15.2.4                Action-Qualifier Software Force
#define PWM_AQCSFRC         0x0000021C // Section 15.2.4                Action-Qualifier Continuous S/W Force Set
// -----    Dead-Band           -----
#define PWM_DBCTL           0x0000021E // Section 15.2.4                Dead-Band Generator Control
#define PWM_DBRED           0x00000220 // Section 15.2.4                Dead-Band Generator Rising Edge Delay Count
#define PWM_DBFED           0x00000222 // Section 15.2.4                Dead-Band Generator Falling Edge Delay Count
// -----    Trip-Zone           -----
#define PWM_TZSEL           0x00000224 // Section 15.2.4                Trip-Zone Select
#define PWM_TZCTL           0x00000228 // Section 15.2.4                Trip-Zone Control
#define PWM_TZEINT          0x0000022A // Section 15.2.4                Trip-Zone Enable Interrupt
#define PWM_TZFLG           0x0000022C // Section 15.2.4                Trip-Zone Flag
#define PWM_TZCLR           0x0000022E // Section 15.2.4                Trip-Zone Clear
#define PWM_TZFRC           0x00000230 // Section 15.2.4                Trip-Zone Force
// -----    Event-Trigger       -----
#define PWM_ETSEL           0x00000232 // Section 15.2.4                Event-Trigger Selection
#define PWM_ETPS            0x00000234 // Section 15.2.4                Event-Trigger Pre-Scale
#define PWM_ETFLG           0x00000236 // Section 15.2.4                Event-Trigger Flag
#define PWM_ETCLR           0x00000238 // Section 15.2.4                Event-Trigger Clear
#define PWM_ETFRC           0x0000023A // Section 15.2.4                Event-Trigger Force
// -----    PWM-Chopper         -----
#define PWM_PCCTL           0x0000023C // Section 15.2.4                PWM-Chopper Control
// -----    High-Resolution PWM ----
#define PWM_HRCTL           0x00000240 // Section 15.2.4                HRPWM Control


#endif /* PWM_CONST_H_ */
