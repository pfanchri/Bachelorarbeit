<?xml version="1.0" encoding="ASCII"?>
<ResourceModel:App xmi:version="2.0" xmlns:xmi="http://www.omg.org/XMI" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:ResourceModel="http://www.infineon.com/Davex/Resource.ecore" name="CLOCK_XMC4" URI="http://resources/4.0.6/app/CLOCK_XMC4/0" description="APP to configure System and Peripheral Clocks." version="4.0.6" minDaveVersion="4.0.0" instanceLabel="CLOCK_XMC4_0" appLabel="">
  <upwardMapList xsi:type="ResourceModel:RequiredApp" href="../../USBD/v4_0_6/USBD_0.app#//@requiredApps.1"/>
  <properties singleton="true" sharable="true"/>
  <virtualSignals name="clk_perbridge_output" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/vs_fpb" hwSignal="fpb" hwResource="//@hwResources.3" visible="true"/>
  <virtualSignals name="clk_ccu_output" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/vs_fccu" hwSignal="fccu" hwResource="//@hwResources.5" visible="true"/>
  <virtualSignals name="clk_external_output" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclk" hwSignal="extclk" hwResource="//@hwResources.9" required="false"/>
  <virtualSignals name="external_clock_pin" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclkpin" hwSignal="pad" hwResource="//@hwResources.12" required="false"/>
  <virtualSignals name="external_clock_pin_signal" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/__pin_vs_extclkpin" hwSignal="pin" hwResource="//@hwResources.13"/>
  <hwResources name="PLL" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_pll" resourceGroupUri="peripheral/scu/0/clkctrl/0/pll" mResGrpUri="peripheral/scu/0/clkctrl/0/pll">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.7"/>
  </hwResources>
  <hwResources name="SYSTEM" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_sys" resourceGroupUri="peripheral/scu/0/clkctrl/0/sys" mResGrpUri="peripheral/scu/0/clkctrl/0/sys">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.8"/>
  </hwResources>
  <hwResources name="CPU" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_cpu" resourceGroupUri="peripheral/scu/0/clkctrl/0/cpu" mResGrpUri="peripheral/scu/0/clkctrl/0/cpu">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.4"/>
  </hwResources>
  <hwResources name="PERIBRIDGE" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_perbridge" resourceGroupUri="peripheral/scu/0/clkctrl/0/perbridge" mResGrpUri="peripheral/scu/0/clkctrl/0/perbridge">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.1"/>
  </hwResources>
  <hwResources name="EBU" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_ebu" resourceGroupUri="peripheral/scu/0/clkctrl/0/ebu" mResGrpUri="peripheral/scu/0/clkctrl/0/ebu">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.5"/>
  </hwResources>
  <hwResources name="CCU" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_ccu" resourceGroupUri="peripheral/scu/0/clkctrl/0/ccu" mResGrpUri="peripheral/scu/0/clkctrl/0/ccu">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.3"/>
  </hwResources>
  <hwResources name="WDT" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_wdt" resourceGroupUri="peripheral/scu/0/clkctrl/0/wdt" mResGrpUri="peripheral/scu/0/clkctrl/0/wdt">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.10"/>
  </hwResources>
  <hwResources name="USB" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_usb" resourceGroupUri="peripheral/scu/0/clkctrl/0/usb" mResGrpUri="peripheral/scu/0/clkctrl/0/usb">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.9"/>
  </hwResources>
  <hwResources name="SDMMC" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_mmc" resourceGroupUri="peripheral/scu/0/clkctrl/0/sdmmc" mResGrpUri="peripheral/scu/0/clkctrl/0/sdmmc">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.6"/>
  </hwResources>
  <hwResources name="EXTCLK" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_extclk" resourceGroupUri="" required="false" mResGrpUri="peripheral/scu/0/clkctrl/0/extclk"/>
  <hwResources name="HIBERNATE" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_hibernate" resourceGroupUri="peripheral/scu/0/pwrctrl/0/hibernate" mResGrpUri="peripheral/scu/0/pwrctrl/0/hibernate">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.2"/>
  </hwResources>
  <hwResources name="RTC" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_rtcclksel" resourceGroupUri="peripheral/scu/0/rtcclksel" mResGrpUri="peripheral/scu/0/rtcclksel">
    <downwardMapList xsi:type="ResourceModel:ResourceGroup" href="../../../HW_RESOURCES/SCU/SCU_0.dd#//@provided.0"/>
  </hwResources>
  <hwResources name="External Clock Output Pin" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/hwres_extclkpin" resourceGroupUri="" required="false" mResGrpUri="port/p/*/pad/*"/>
  <hwResources name="external_clock_pin" URI="http://resources/4.0.6/app/CLOCK_XMC4/0/__pin_hwres_extclkpin" resourceGroupUri="" required="false" mResGrpUri="devicepackage/0/*"/>
  <connections URI="http://resources/4.0.6/app/CLOCK_XMC4/0/http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclk/http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclkpin" systemDefined="true" sourceSignal="clk_external_output" targetSignal="external_clock_pin" srcVirtualSignal="//@virtualSignals.2" targetVirtualSignal="//@virtualSignals.3"/>
  <connections URI="http://resources/4.0.6/app/CLOCK_XMC4/0/http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclkpin/http://resources/4.0.6/app/CLOCK_XMC4/0/__pin_vs_extclkpin" systemDefined="true" sourceSignal="external_clock_pin" targetSignal="external_clock_pin_signal" srcVirtualSignal="//@virtualSignals.3" targetVirtualSignal="//@virtualSignals.4"/>
  <connections URI="http://resources/4.0.6/app/CLOCK_XMC4/0/http://resources/4.0.6/app/CLOCK_XMC4/0/__pin_vs_extclkpin/http://resources/4.0.6/app/CLOCK_XMC4/0/vs_extclkpin" systemDefined="true" sourceSignal="external_clock_pin_signal" targetSignal="external_clock_pin" srcVirtualSignal="//@virtualSignals.4" targetVirtualSignal="//@virtualSignals.3"/>
</ResourceModel:App>
