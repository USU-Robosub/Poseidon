/**
  * Created on: Thr Jan 22 2015
  * Author: TekuConcept
  */

#ifndef PWM_CONST_H_
#define PWM_CONST_H_


// Subsystem
#define PWM_SUB0            0x48300000 ///< See <a href="/documentation/AM335x_TRM.pdf#page=161">Section 2.1</a> of the Technical Reference Manual
#define PWM_SUB1            0x48302000 ///< See <a href="/documentation/AM335x_TRM.pdf#page=161">Section 2.1</a> of the Technical Reference Manual
#define PWM_SUB2            0x48304000 ///< See <a href="/documentation/AM335x_TRM.pdf#page=161">Section 2.1</a> of the Technical Reference Manual

// Specific (pg 1489)
#define PWM_IDVER           0x00000000 ///< ID Version: See <a href="/documentation/AM335x_TRM.pdf#page=1490">Section 15.1.3</a> of the Technical Reference Manual
#define PWM_SYSCONFIG       0x00000004 ///< System Configuration: See <a href="/documentation/AM335x_TRM.pdf#page=1491">Section 15.1.3</a> of the Technical Reference Manual
#define PWM_CLKCONFIG       0x00000008 ///< Clock Configuration: See <a href="/documentation/AM335x_TRM.pdf#page=1492">Section 15.1.3</a> of the Technical Reference Manual
#define PWM_CLKSTATUS       0x0000000C ///< Clock Status: See <a href="/documentation/AM335x_TRM.pdf#page=1493">Section 2.1</a> of the Technical Reference Manual

// eCAP (pg 1634)
#define PWM_TSCTR           0x00000100 ///< Time-Stamp Counter: See <a href="/documentation/AM335x_TRM.pdf#page=1635">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_CTRPHS          0x00000104 ///< Counter Phase Offset Value: See <a href="/documentation/AM335x_TRM.pdf#page=1636">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_CAP1            0x00000108 ///< Capture 1: See <a href="/documentation/AM335x_TRM.pdf#page=1637">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_CAP2            0x0000010C ///< Capture 2: See <a href="/documentation/AM335x_TRM.pdf#page=1638">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_CAP3            0x00000110 ///< Capture 3: See <a href="/documentation/AM335x_TRM.pdf#page=1639">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_CAP4            0x00000114 ///< Capture 4: See <a href="/documentation/AM335x_TRM.pdf#page=1640">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECCTL1          0x00000128 ///< Capture Control 1: See <a href="/documentation/AM335x_TRM.pdf#page=1641">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECCTL2          0x0000012A ///< Capture Control 2: See <a href="/documentation/AM335x_TRM.pdf#page=1643">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECEINT          0x0000012C ///< Capture Interrupt Enable: See <a href="/documentation/AM335x_TRM.pdf#page=1645">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECFLG           0x0000012E ///< Capture Interrupt Flag: See <a href="/documentation/AM335x_TRM.pdf#page=1646">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECCLR           0x00000130 ///< Capture Interrupt Clear: See <a href="/documentation/AM335x_TRM.pdf#page=1647">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_ECFRC           0x00000132 ///< Capture Interrupt Force: See <a href="/documentation/AM335x_TRM.pdf#page=1648">Section 15.3.4.1</a> of the Technical Reference Manual
#define PWM_eCAP_REVID      0x0000015C ///< Revision ID: See <a href="/documentation/AM335x_TRM.pdf#page=1649">Section 15.3.4.1</a> of the Technical Reference Manual

// eQEP (pg 1672)
#define PWM_QPOSCNT         0x00000180 ///< Position Counter: See <a href="/documentation/AM335x_TRM.pdf#page=1673">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSINIT        0x00000184 ///< Position Counter Initialization: See <a href="/documentation/AM335x_TRM.pdf#page=1673">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSMAX         0x00000188 ///< Maximum Position Count: See <a href="/documentation/AM335x_TRM.pdf#page=1673">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSCMP         0x0000018C ///< Position-Compare: See <a href="/documentation/AM335x_TRM.pdf#page=1674">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSILAT        0x00000190 ///< Index Position Latch: See <a href="/documentation/AM335x_TRM.pdf#page=1674">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSSLAT        0x00000194 ///< Strobe Position Latch: See <a href="/documentation/AM335x_TRM.pdf#page=1674">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_APOSLAT         0x00000198 ///< Position Counter Latch: See <a href="/documentation/AM335x_TRM.pdf#page=1675">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QUTMR           0x0000019C ///< Unit Timer: See <a href="/documentation/AM335x_TRM.pdf#page=1675">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QUPRD           0x000001A0 ///< Unit Period: See <a href="/documentation/AM335x_TRM.pdf#page=1675">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QWDTMR          0x000001A4 ///< Watchdog Timer: See <a href="/documentation/AM335x_TRM.pdf#page=1676">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QWDPRD          0x000001A6 ///< Watchdog Period: See <a href="/documentation/AM335x_TRM.pdf#page=1676">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QDECCTL         0x000001A8 ///< Decoder Control: See <a href="/documentation/AM335x_TRM.pdf#page=1677">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QEPCTL          0x000001AA ///< Control: See <a href="/documentation/AM335x_TRM.pdf#page=1678">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCAPCTL         0x000001AC ///< Capture Control: See <a href="/documentation/AM335x_TRM.pdf#page=1680">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QPOSCTL         0x000001AE ///< Position-Compare Control: See <a href="/documentation/AM335x_TRM.pdf#page=1681">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QEINT           0x000001B0 ///< Interrupt Enable: See <a href="/documentation/AM335x_TRM.pdf#page=1682">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QFLG            0x000001B2 ///< Interrupt Flag: See <a href="/documentation/AM335x_TRM.pdf#page=1683">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCLR            0x000001B4 ///< Interrupt Clear: See <a href="/documentation/AM335x_TRM.pdf#page=1684">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QFRC            0x000001B6 ///< Interrupt Force: See <a href="/documentation/AM335x_TRM.pdf#page=1686">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QEPSTS          0x000001B8 ///< Status: See <a href="/documentation/AM335x_TRM.pdf#page=1687">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCTMR           0x000001BA ///< Capture Timer: See <a href="/documentation/AM335x_TRM.pdf#page=1688">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCPRD           0x000001BC ///< Capture Period: See <a href="/documentation/AM335x_TRM.pdf#page=1688">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCTMRLAT        0x000001BE ///< Capture Timer Latch: See <a href="/documentation/AM335x_TRM.pdf#page=1688">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_QCPRDLAT        0x000001C0 ///< Capture Period Latch: See <a href="/documentation/AM335x_TRM.pdf#page=1689">Section 15.4.3</a> of the Technical Reference Manual
#define PWM_eQEP_REVID      0x000001DC ///< Revision ID: See <a href="/documentation/AM335x_TRM.pdf#page=1689">Section 15.4.3</a> of the Technical Reference Manual

// ePWM (pg 1581)
// -----    Time-Based          -----
#define PWM_TBCTL           0x00000200 ///< Time-Base Control: See <a href="/documentation/AM335x_TRM.pdf#page=1582">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TBSTS           0x00000202 ///< Time-Base Status: See <a href="/documentation/AM335x_TRM.pdf#page=1584">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TBPHSHR         0x00000204 ///< Extension for HRPWM Phase: See <a href="/documentation/AM335x_TRM.pdf#page=1605">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TBPHS           0x00000206 ///< Time-Base Phase: See <a href="/documentation/AM335x_TRM.pdf#page=1584">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TBCNT           0x00000208 ///< Time-Base Counter: See <a href="/documentation/AM335x_TRM.pdf#page=1585">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TBPRD           0x0000020A ///< Time-Base Period: See <a href="/documentation/AM335x_TRM.pdf#page=1586">Section 15.2.4</a> of the Technical Reference Manual
// -----    Counter-Compare     -----
#define PWM_CMPCTL          0x0000020E ///< Counter-Compare Control: See <a href="/documentation/AM335x_TRM.pdf#page=1587">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_CMPAHR          0x00000210 ///< Extension for HRPWM Counter Compare A: See <a href="/documentation/AM335x_TRM.pdf#page=1605">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_CMPA            0x00000212 ///< Counter-Compare A: See <a href="/documentation/AM335x_TRM.pdf#page=1588">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_CMPB            0x00000214 ///< Counter-Compare B: See <a href="/documentation/AM335x_TRM.pdf#page=1589">Section 15.2.4</a> of the Technical Reference Manual
// -----    Action-Qualifier    -----
#define PWM_AQCTLA          0x00000216 ///< Action-Qualifier Control for Output A (ePWMxA): See <a href="/documentation/AM335x_TRM.pdf#page=1590">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_AQCTLB          0x00000218 ///< Action-Qualifier Control for Output B (ePWMxB): See <a href="/documentation/AM335x_TRM.pdf#page=1591">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_AQSFRC          0x0000021A ///< Action-Qualifier Software Force: See <a href="/documentation/AM335x_TRM.pdf#page=1592">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_AQCSFRC         0x0000021C ///< Action-Qualifier Continuous S/W Force Set: See <a href="/documentation/AM335x_TRM.pdf#page=1593">Section 15.2.4</a> of the Technical Reference Manual
// -----    Dead-Band           -----
#define PWM_DBCTL           0x0000021E ///< Dead-Band Generator Control: See <a href="/documentation/AM335x_TRM.pdf#page=1594">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_DBRED           0x00000220 ///< Dead-Band Generator Rising Edge Delay Count: See <a href="/documentation/AM335x_TRM.pdf#page=1595">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_DBFED           0x00000222 ///< Dead-Band Generator Falling Edge Delay Count: See <a href="/documentation/AM335x_TRM.pdf#page=1595">Section 15.2.4</a> of the Technical Reference Manual
// -----    Trip-Zone           -----
#define PWM_TZSEL           0x00000224 ///< Trip-Zone Select: See <a href="/documentation/AM335x_TRM.pdf#page=1596">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TZCTL           0x00000228 ///< Trip-Zone Control: See <a href="/documentation/AM335x_TRM.pdf#page=1597">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TZEINT          0x0000022A ///< Trip-Zone Enable Interrupt: See <a href="/documentation/AM335x_TRM.pdf#page=1597">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TZFLG           0x0000022C ///< Trip-Zone Flag: See <a href="/documentation/AM335x_TRM.pdf#page=1598">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TZCLR           0x0000022E ///< Trip-Zone Clear: See <a href="/documentation/AM335x_TRM.pdf#page=1599">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_TZFRC           0x00000230 ///< Trip-Zone Force: See <a href="/documentation/AM335x_TRM.pdf#page=1599">Section 15.2.4</a> of the Technical Reference Manual
// -----    Event-Trigger       -----
#define PWM_ETSEL           0x00000232 ///< Event-Trigger Selection: See <a href="/documentation/AM335x_TRM.pdf#page=1600">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_ETPS            0x00000234 ///< Event-Trigger Pre-Scale: See <a href="/documentation/AM335x_TRM.pdf#page=1601">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_ETFLG           0x00000236 ///< Event-Trigger Flag: See <a href="/documentation/AM335x_TRM.pdf#page=1602">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_ETCLR           0x00000238 ///< Event-Trigger Clear: See <a href="/documentation/AM335x_TRM.pdf#page=1602">Section 15.2.4</a> of the Technical Reference Manual
#define PWM_ETFRC           0x0000023A ///< Event-Trigger Force: See <a href="/documentation/AM335x_TRM.pdf#page=1603">Section 15.2.4</a> of the Technical Reference Manual
// -----    PWM-Chopper         -----
#define PWM_PCCTL           0x0000023C ///< PWM-Chopper Control: See <a href="/documentation/AM335x_TRM.pdf#page=1604">Section 15.2.4</a> of the Technical Reference Manual
// -----    High-Resolution PWM ----
#define PWM_HRCTL           0x00000240 ///< HRPWM Control: See <a href="/documentation/AM335x_TRM.pdf#page=1606">Section 15.2.4</a> of the Technical Reference Manual


#endif /* PWM_CONST_H_ */
