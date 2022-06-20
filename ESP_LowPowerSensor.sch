<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="nodemcu">
<packages>
<package name="NODEMCUESP8266">
<description>Node Mcu esp8266 12E
LIBRARY BY SDTECH ROBOTICS
(Shubham Devkar Technology Solutions)</description>
<pad name="26" x="-10.16" y="5.08" drill="0.8" shape="long"/>
<pad name="25" x="-10.16" y="2.54" drill="0.8" shape="long"/>
<pad name="24" x="-10.16" y="0" drill="0.8" shape="long"/>
<pad name="23" x="-10.16" y="-2.54" drill="0.8" shape="long"/>
<pad name="22" x="-10.16" y="-5.08" drill="0.8" shape="long"/>
<pad name="21" x="-10.16" y="-7.62" drill="0.8" shape="long"/>
<pad name="27" x="-10.16" y="7.62" drill="0.8" shape="long"/>
<pad name="20" x="-10.16" y="-10.16" drill="0.8" shape="long"/>
<pad name="19" x="-10.16" y="-12.7" drill="0.8" shape="long"/>
<pad name="18" x="-10.16" y="-15.24" drill="0.8" shape="long"/>
<pad name="28" x="-10.16" y="10.16" drill="0.8" shape="long"/>
<pad name="17" x="-10.16" y="-17.78" drill="0.8" shape="long"/>
<pad name="29" x="-10.16" y="12.7" drill="0.8" shape="long"/>
<pad name="16" x="-10.16" y="-20.32" drill="0.8" shape="long"/>
<pad name="1" x="15.24" y="15.24" drill="0.8" shape="long"/>
<pad name="2" x="15.24" y="12.7" drill="0.8" shape="long"/>
<pad name="3" x="15.24" y="10.16" drill="0.8" shape="long"/>
<pad name="4" x="15.24" y="7.62" drill="0.8" shape="long"/>
<pad name="5" x="15.24" y="5.08" drill="0.8" shape="long"/>
<pad name="6" x="15.24" y="2.54" drill="0.8" shape="long"/>
<pad name="7" x="15.24" y="0" drill="0.8" shape="long"/>
<pad name="8" x="15.24" y="-2.54" drill="0.8" shape="long"/>
<pad name="9" x="15.24" y="-5.08" drill="0.8" shape="long"/>
<pad name="10" x="15.24" y="-7.62" drill="0.8" shape="long"/>
<pad name="12" x="15.24" y="-12.7" drill="0.8" shape="long"/>
<pad name="13" x="15.24" y="-15.24" drill="0.8" shape="long"/>
<pad name="14" x="15.24" y="-17.78" drill="0.8" shape="long"/>
<pad name="15" x="15.24" y="-20.32" drill="0.8" shape="long"/>
<wire x1="-13.97" y1="-26.67" x2="19.05" y2="-26.67" width="0.127" layer="21"/>
<wire x1="19.05" y1="-26.67" x2="19.05" y2="22.86" width="0.127" layer="21"/>
<wire x1="-13.97" y1="-26.67" x2="-13.97" y2="22.86" width="0.127" layer="21"/>
<wire x1="-13.97" y1="22.86" x2="19.05" y2="22.86" width="0.127" layer="21"/>
<wire x1="12.7" y1="-19.05" x2="12.7" y2="-24.13" width="0.254" layer="2"/>
<wire x1="12.7" y1="-24.13" x2="11.43" y2="-24.13" width="0.254" layer="2"/>
<wire x1="11.43" y1="-24.13" x2="11.43" y2="-20.32" width="0.254" layer="2"/>
<wire x1="11.43" y1="-20.32" x2="10.16" y2="-20.32" width="0.254" layer="2"/>
<wire x1="10.16" y1="-20.32" x2="10.16" y2="-24.13" width="0.254" layer="2"/>
<wire x1="10.16" y1="-24.13" x2="8.89" y2="-24.13" width="0.254" layer="2"/>
<wire x1="8.89" y1="-24.13" x2="8.89" y2="-20.32" width="0.254" layer="2"/>
<wire x1="8.89" y1="-20.32" x2="7.62" y2="-20.32" width="0.254" layer="2"/>
<wire x1="7.62" y1="-20.32" x2="7.62" y2="-24.13" width="0.254" layer="2"/>
<wire x1="7.62" y1="-24.13" x2="6.35" y2="-24.13" width="0.254" layer="2"/>
<wire x1="6.35" y1="-24.13" x2="6.35" y2="-20.32" width="0.254" layer="2"/>
<wire x1="6.35" y1="-20.32" x2="5.08" y2="-20.32" width="0.254" layer="2"/>
<wire x1="5.08" y1="-20.32" x2="5.08" y2="-24.13" width="0.254" layer="2"/>
<wire x1="6.35" y1="-19.05" x2="12.7" y2="-19.05" width="0.254" layer="2"/>
<wire x1="5.08" y1="-24.13" x2="1.27" y2="-24.13" width="0.254" layer="2"/>
<rectangle x1="-1.27" y1="-17.78" x2="8.89" y2="-7.62" layer="21"/>
<text x="1.27" y="-11.43" size="1.27" layer="2" rot="R90">Wifi</text>
<text x="1.27" y="-3.81" size="1.778" layer="21" rot="R90">NODE MCU</text>
<text x="6.35" y="-1.27" size="1.4224" layer="21" rot="R90">SDTECH</text>
<pad name="11" x="15.24" y="-10.16" drill="0.8" shape="long"/>
<pad name="30" x="-10.16" y="15.24" drill="0.8" shape="long"/>
</package>
</packages>
<symbols>
<symbol name="NODEMCUESP8266">
<description>Node Mcu esp8266 12E
LIBRARY BY SDTECH ROBOTICS
(Shubham Devkar Technology Solutions)</description>
<pin name="1" x="-10.16" y="17.78" length="middle"/>
<pin name="2" x="-10.16" y="15.24" length="middle"/>
<pin name="3" x="-10.16" y="12.7" length="middle"/>
<pin name="4" x="-10.16" y="10.16" length="middle"/>
<pin name="5" x="-10.16" y="7.62" length="middle"/>
<pin name="6" x="-10.16" y="5.08" length="middle"/>
<pin name="7" x="-10.16" y="2.54" length="middle"/>
<pin name="8" x="-10.16" y="0" length="middle"/>
<pin name="9" x="-10.16" y="-2.54" length="middle"/>
<pin name="10" x="-10.16" y="-5.08" length="middle"/>
<pin name="11" x="-10.16" y="-7.62" length="middle"/>
<pin name="12" x="-10.16" y="-10.16" length="middle"/>
<pin name="13" x="-10.16" y="-12.7" length="middle"/>
<pin name="14" x="-10.16" y="-15.24" length="middle"/>
<pin name="15" x="-10.16" y="-17.78" length="middle"/>
<pin name="16" x="-25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="17" x="-25.4" y="-15.24" length="middle" rot="R180"/>
<pin name="18" x="-25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="19" x="-25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="20" x="-25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="21" x="-25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="22" x="-25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="23" x="-25.4" y="0" length="middle" rot="R180"/>
<pin name="24" x="-25.4" y="2.54" length="middle" rot="R180"/>
<pin name="25" x="-25.4" y="5.08" length="middle" rot="R180"/>
<pin name="26" x="-25.4" y="7.62" length="middle" rot="R180"/>
<pin name="27" x="-25.4" y="10.16" length="middle" rot="R180"/>
<pin name="28" x="-25.4" y="12.7" length="middle" rot="R180"/>
<pin name="29" x="-25.4" y="15.24" length="middle" rot="R180"/>
<pin name="30" x="-25.4" y="17.78" length="middle" rot="R180"/>
<wire x1="-25.4" y1="-20.32" x2="-10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-20.32" x2="-10.16" y2="22.86" width="0.254" layer="94"/>
<wire x1="-10.16" y1="22.86" x2="-25.4" y2="22.86" width="0.254" layer="94"/>
<wire x1="-25.4" y1="22.86" x2="-25.4" y2="-20.32" width="0.254" layer="94"/>
<text x="-17.78" y="-2.54" size="1.27" layer="94" rot="R90">Nodemcu</text>
<text x="-15.24" y="-2.54" size="1.27" layer="94" rot="R90">sdtech </text>
</symbol>
</symbols>
<devicesets>
<deviceset name="NODEMCUESP8266" uservalue="yes">
<description>Node Mcu esp8266 12E
LIBRARY BY SDTECH ROBOTICS
(Shubham Devkar Technology Solutions)</description>
<gates>
<gate name="G$1" symbol="NODEMCUESP8266" x="7.62" y="7.62"/>
</gates>
<devices>
<device name="" package="NODEMCUESP8266">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="+5V" urn="urn:adsk.eagle:symbol:26929/1" library_version="1">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" urn="urn:adsk.eagle:component:26963/1" prefix="P+" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="DHT11">
<packages>
<package name="DHT11">
<wire x1="-6.096" y1="8.0264" x2="6.0452" y2="8.0264" width="0.127" layer="21"/>
<wire x1="6.0452" y1="8.0264" x2="6.0452" y2="-8.2296" width="0.127" layer="21"/>
<wire x1="6.0452" y1="-8.2296" x2="-6.096" y2="-8.2296" width="0.127" layer="21"/>
<wire x1="-6.096" y1="-8.2296" x2="-6.096" y2="8.0264" width="0.127" layer="21"/>
<wire x1="-0.1524" y1="1.9812" x2="0.1524" y2="1.9812" width="0.127" layer="21"/>
<wire x1="0.1524" y1="1.9812" x2="0.1524" y2="1.6764" width="0.127" layer="21"/>
<wire x1="0.1524" y1="1.6764" x2="-0.1524" y2="1.6764" width="0.127" layer="21"/>
<wire x1="-0.1524" y1="1.6764" x2="-0.1524" y2="1.9812" width="0.127" layer="21"/>
<wire x1="-5.6388" y1="2.032" x2="-5.334" y2="2.032" width="0.127" layer="21"/>
<wire x1="-5.334" y1="2.032" x2="-5.334" y2="1.7272" width="0.127" layer="21"/>
<wire x1="-5.334" y1="1.7272" x2="-5.6388" y2="1.7272" width="0.127" layer="21"/>
<wire x1="-5.6388" y1="1.7272" x2="-5.6388" y2="2.032" width="0.127" layer="21"/>
<wire x1="5.334" y1="2.032" x2="5.6388" y2="2.032" width="0.127" layer="21"/>
<wire x1="5.6388" y1="2.032" x2="5.6388" y2="1.7272" width="0.127" layer="21"/>
<wire x1="5.6388" y1="1.7272" x2="5.334" y2="1.7272" width="0.127" layer="21"/>
<wire x1="5.334" y1="1.7272" x2="5.334" y2="2.032" width="0.127" layer="21"/>
<wire x1="-2.8956" y1="2.032" x2="-2.5908" y2="2.032" width="0.127" layer="21"/>
<wire x1="-2.5908" y1="2.032" x2="-2.5908" y2="1.7272" width="0.127" layer="21"/>
<wire x1="-2.5908" y1="1.7272" x2="-2.8956" y2="1.7272" width="0.127" layer="21"/>
<wire x1="-2.8956" y1="1.7272" x2="-2.8956" y2="2.032" width="0.127" layer="21"/>
<wire x1="2.5908" y1="2.032" x2="2.8956" y2="2.032" width="0.127" layer="21"/>
<wire x1="2.8956" y1="2.032" x2="2.8956" y2="1.7272" width="0.127" layer="21"/>
<wire x1="2.8956" y1="1.7272" x2="2.5908" y2="1.7272" width="0.127" layer="21"/>
<wire x1="2.5908" y1="1.7272" x2="2.5908" y2="2.032" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-0.5588" x2="0.1016" y2="-0.5588" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-0.5588" x2="0.1016" y2="-0.8636" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-0.8636" x2="-0.2032" y2="-0.8636" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-0.8636" x2="-0.2032" y2="-0.5588" width="0.127" layer="21"/>
<wire x1="-5.6896" y1="-0.508" x2="-5.3848" y2="-0.508" width="0.127" layer="21"/>
<wire x1="-5.3848" y1="-0.508" x2="-5.3848" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="-5.3848" y1="-0.8128" x2="-5.6896" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="-5.6896" y1="-0.8128" x2="-5.6896" y2="-0.508" width="0.127" layer="21"/>
<wire x1="5.2832" y1="-0.508" x2="5.588" y2="-0.508" width="0.127" layer="21"/>
<wire x1="5.588" y1="-0.508" x2="5.588" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="5.588" y1="-0.8128" x2="5.2832" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="5.2832" y1="-0.8128" x2="5.2832" y2="-0.508" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-0.508" x2="-2.6416" y2="-0.508" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-0.508" x2="-2.6416" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-0.8128" x2="-2.9464" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-0.8128" x2="-2.9464" y2="-0.508" width="0.127" layer="21"/>
<wire x1="2.54" y1="-0.508" x2="2.8448" y2="-0.508" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-0.508" x2="2.8448" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-0.8128" x2="2.54" y2="-0.8128" width="0.127" layer="21"/>
<wire x1="2.54" y1="-0.8128" x2="2.54" y2="-0.508" width="0.127" layer="21"/>
<wire x1="-0.1524" y1="7.366" x2="0.1524" y2="7.366" width="0.127" layer="21"/>
<wire x1="0.1524" y1="7.366" x2="0.1524" y2="7.0612" width="0.127" layer="21"/>
<wire x1="0.1524" y1="7.0612" x2="-0.1524" y2="7.0612" width="0.127" layer="21"/>
<wire x1="-0.1524" y1="7.0612" x2="-0.1524" y2="7.366" width="0.127" layer="21"/>
<wire x1="-2.8956" y1="7.4168" x2="-2.5908" y2="7.4168" width="0.127" layer="21"/>
<wire x1="-2.5908" y1="7.4168" x2="-2.5908" y2="7.112" width="0.127" layer="21"/>
<wire x1="-2.5908" y1="7.112" x2="-2.8956" y2="7.112" width="0.127" layer="21"/>
<wire x1="-2.8956" y1="7.112" x2="-2.8956" y2="7.4168" width="0.127" layer="21"/>
<wire x1="2.5908" y1="7.4168" x2="2.8956" y2="7.4168" width="0.127" layer="21"/>
<wire x1="2.8956" y1="7.4168" x2="2.8956" y2="7.112" width="0.127" layer="21"/>
<wire x1="2.8956" y1="7.112" x2="2.5908" y2="7.112" width="0.127" layer="21"/>
<wire x1="2.5908" y1="7.112" x2="2.5908" y2="7.4168" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="4.826" x2="0.1016" y2="4.826" width="0.127" layer="21"/>
<wire x1="0.1016" y1="4.826" x2="0.1016" y2="4.5212" width="0.127" layer="21"/>
<wire x1="0.1016" y1="4.5212" x2="-0.2032" y2="4.5212" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="4.5212" x2="-0.2032" y2="4.826" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="4.8768" x2="-2.6416" y2="4.8768" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="4.8768" x2="-2.6416" y2="4.572" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="4.572" x2="-2.9464" y2="4.572" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="4.572" x2="-2.9464" y2="4.8768" width="0.127" layer="21"/>
<wire x1="2.54" y1="4.8768" x2="2.8448" y2="4.8768" width="0.127" layer="21"/>
<wire x1="2.8448" y1="4.8768" x2="2.8448" y2="4.572" width="0.127" layer="21"/>
<wire x1="2.8448" y1="4.572" x2="2.54" y2="4.572" width="0.127" layer="21"/>
<wire x1="2.54" y1="4.572" x2="2.54" y2="4.8768" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-3.302" x2="0.1016" y2="-3.302" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-3.302" x2="0.1016" y2="-3.6068" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-3.6068" x2="-0.2032" y2="-3.6068" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-3.6068" x2="-0.2032" y2="-3.302" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-3.2512" x2="-2.6416" y2="-3.2512" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-3.2512" x2="-2.6416" y2="-3.556" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-3.556" x2="-2.9464" y2="-3.556" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-3.556" x2="-2.9464" y2="-3.2512" width="0.127" layer="21"/>
<wire x1="2.54" y1="-3.2512" x2="2.8448" y2="-3.2512" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-3.2512" x2="2.8448" y2="-3.556" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-3.556" x2="2.54" y2="-3.556" width="0.127" layer="21"/>
<wire x1="2.54" y1="-3.556" x2="2.54" y2="-3.2512" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-5.9944" x2="0.1016" y2="-5.9944" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-5.9944" x2="0.1016" y2="-6.2992" width="0.127" layer="21"/>
<wire x1="0.1016" y1="-6.2992" x2="-0.2032" y2="-6.2992" width="0.127" layer="21"/>
<wire x1="-0.2032" y1="-6.2992" x2="-0.2032" y2="-5.9944" width="0.127" layer="21"/>
<wire x1="-5.6896" y1="-5.9436" x2="-5.3848" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="-5.3848" y1="-5.9436" x2="-5.3848" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="-5.3848" y1="-6.2484" x2="-5.6896" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="-5.6896" y1="-6.2484" x2="-5.6896" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="5.2832" y1="-5.9436" x2="5.588" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="5.588" y1="-5.9436" x2="5.588" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="5.588" y1="-6.2484" x2="5.2832" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="5.2832" y1="-6.2484" x2="5.2832" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-5.9436" x2="-2.6416" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-5.9436" x2="-2.6416" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="-2.6416" y1="-6.2484" x2="-2.9464" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="-2.9464" y1="-6.2484" x2="-2.9464" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="2.54" y1="-5.9436" x2="2.8448" y2="-5.9436" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-5.9436" x2="2.8448" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="2.8448" y1="-6.2484" x2="2.54" y2="-6.2484" width="0.127" layer="21"/>
<wire x1="2.54" y1="-6.2484" x2="2.54" y2="-5.9436" width="0.127" layer="21"/>
<text x="-2.5908" y="5.334" size="1.27" layer="25">DHT11</text>
<pad name="VCC" x="-3.81" y="-11.43" drill="0.8" diameter="2.1844" shape="square"/>
<pad name="DATA" x="-1.27" y="-11.43" drill="0.8" diameter="2.1844" shape="square"/>
<pad name="NO" x="1.27" y="-11.43" drill="0.8" diameter="2.1844" shape="square"/>
<pad name="GND" x="3.81" y="-11.43" drill="0.8" diameter="2.1844" shape="square"/>
</package>
</packages>
<symbols>
<symbol name="DHT11">
<wire x1="-5.08" y1="7.62" x2="7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="7.62" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<text x="-2.286" y="5.08" size="1.778" layer="95">DHT11</text>
<pin name="VCC" x="-2.54" y="-12.7" length="middle" rot="R90"/>
<pin name="DATA" x="0" y="-12.7" length="middle" rot="R90"/>
<pin name="NO" x="2.54" y="-12.7" length="middle" rot="R90"/>
<pin name="GND" x="5.08" y="-12.7" length="middle" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DHT11" uservalue="yes">
<description>DHT11 Czujnik temperatury i wilgotności</description>
<gates>
<gate name="G$1" symbol="DHT11" x="-0.762" y="0.254"/>
</gates>
<devices>
<device name="" package="DHT11">
<connects>
<connect gate="G$1" pin="DATA" pad="DATA"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="NO" pad="NO"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="nodemcu" deviceset="NODEMCUESP8266" device=""/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="P+1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="+5V" device=""/>
<part name="U$2" library="DHT11" deviceset="DHT11" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="86.36" y="55.88" smashed="yes"/>
<instance part="GND1" gate="1" x="91.44" y="66.04" smashed="yes">
<attribute name="VALUE" x="88.9" y="63.5" size="1.778" layer="96"/>
</instance>
<instance part="P+1" gate="1" x="91.44" y="78.74" smashed="yes">
<attribute name="VALUE" x="88.9" y="73.66" size="1.778" layer="96" rot="R90"/>
</instance>
<instance part="U$2" gate="G$1" x="25.4" y="66.04" smashed="yes"/>
</instances>
<busses>
</busses>
<nets>
<net name="+5V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="1"/>
<wire x1="76.2" y1="73.66" x2="91.44" y2="73.66" width="0.1524" layer="91"/>
<pinref part="P+1" gate="1" pin="+5V"/>
<wire x1="91.44" y1="73.66" x2="91.44" y2="76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="2"/>
<wire x1="76.2" y1="71.12" x2="91.44" y2="71.12" width="0.1524" layer="91"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="91.44" y1="71.12" x2="91.44" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="25"/>
<wire x1="60.96" y1="60.96" x2="40.64" y2="60.96" width="0.1524" layer="91"/>
<wire x1="40.64" y1="60.96" x2="40.64" y2="43.18" width="0.1524" layer="91"/>
<wire x1="40.64" y1="43.18" x2="25.4" y2="43.18" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="DATA"/>
<wire x1="25.4" y1="43.18" x2="25.4" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="VCC"/>
<wire x1="22.86" y1="53.34" x2="22.86" y2="48.26" width="0.1524" layer="91"/>
<wire x1="22.86" y1="48.26" x2="10.16" y2="48.26" width="0.1524" layer="91"/>
<wire x1="10.16" y1="48.26" x2="10.16" y2="81.28" width="0.1524" layer="91"/>
<wire x1="10.16" y1="81.28" x2="50.8" y2="81.28" width="0.1524" layer="91"/>
<wire x1="50.8" y1="81.28" x2="50.8" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="30"/>
<wire x1="50.8" y1="73.66" x2="60.96" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="29"/>
<wire x1="60.96" y1="71.12" x2="35.56" y2="71.12" width="0.1524" layer="91"/>
<wire x1="35.56" y1="71.12" x2="35.56" y2="50.8" width="0.1524" layer="91"/>
<wire x1="35.56" y1="50.8" x2="30.48" y2="50.8" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="GND"/>
<wire x1="30.48" y1="50.8" x2="30.48" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="16"/>
<wire x1="60.96" y1="38.1" x2="55.88" y2="38.1" width="0.1524" layer="91"/>
<wire x1="55.88" y1="38.1" x2="55.88" y2="30.48" width="0.1524" layer="91"/>
<wire x1="55.88" y1="30.48" x2="86.36" y2="30.48" width="0.1524" layer="91"/>
<wire x1="86.36" y1="30.48" x2="86.36" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3"/>
<wire x1="86.36" y1="68.58" x2="76.2" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
