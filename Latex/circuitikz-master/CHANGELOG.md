<!--- CircuiTikz - Changelog --->
The major changes among the different circuitikz versions are listed here. See <https://github.com/mredaelli/circuitikz/commits> for a full list of changes.

* Version 0.6 (unreleased)
	- Add new sources voosource and ioosource (double zero-style)
	- All diode can now drawn in a stroked way, just use globel option "strokediode" or stroke instead of full/empty, or D-
	- Improved Shape of Diodes:tunnel diode, Zener diode, schottky diode (bit longer lines at cathode)
	- Reworked igbt: New anchors G,gate and new L-shaped form Lnigbt, Lpigbt
	- Improved shape of all fet-transistors and mirrored p-chan fets as default, as pnp, pmos, pfet are already. This means a backward-incompatibility, but smaller code, because p-channels mosfet are by default in the correct direction(source at top). Just remove the 'yscale=-1' from your p-chan fets at old pictures.

* Version 0.5 (2016-04-24)
	- new option boxed and dashed for hf-symbols
	- new option solderdot to enable/disable solderdot at source port of some fets
	- new parts: photovoltaic source, piezo crystal, electrolytic capacitor, electromechanical device(motor, generator)
	- corrected voltage and current direction(option to use old behaviour)
	- option to show body diode at fet transistors

* Version 0.4
    - minor improvements to documentation
    - comply with TDS
    - merge high frequency symbols by Stefan Erhardt
    - added switch (not opening nor closing)
    - added solder dot in some transistors
    - improved ConTeXt compatibility

* Version 0.3.1
    - different management of color...
    - fixed typo in documentation
    - fixed an error in the angle computation in voltage and current routines
    - fixed problem with label size when scaling a tikz picture
    - added gas filled surge arrester
    - added compatibility option to work with Tikz's own circuit library
    - fixed infinite in arctan computation

* Version 0.3.0
	- fixed gate node for a few transistors
    - added mixer
    - added fully differential op amp (by Kristofer M. Monisit)
    - now general settings for the drawing of voltage can be overridden for specific components
    - made arrows more homogeneous (either the current one, or latex' bt pgf)
    - added the single battery cell
    - added fuse and asymmetric fuse
    - added toggle switch
    - added varistor, photoresistor, thermocouple, push button
    - added thermistor, thermistor ptc, thermistor ptc
    - fixed misalignment of voltage label in vertical bipoles with names
    - added isfet
    - added noiseless, protective, chassis, signal and reference grounds (Luigi «Liverpool»)

* Version 0.2.4	
	- added square voltage source (contributed by Alistair Kwan)
	- added buffer and plain amplifier (contributed by Danilo Piazzalunga)
	- added squid and barrier (contributed by  Cor Molenaar)
	- added antenna and transmission line symbols contributed by Leonardo Azzinnari
	- added the changeover switch spdt (suggestion of Fabio Maria Antoniali)
	- rename of context.tex and context.pdf (thanks to Karl Berry)
	- updated the email address
    - in documentation, fixed wrong (non-standard) labelling of the axis in an example (thanks to prof. Claudio Beccaria)
    - fixed scaling inconsistencies in quadrupoles    
    - fixed division by zero error on certain vertical paths
    - introduced options straighlabels, rotatelabels, smartlabels

* Version 0.2.3
	- fixed compatibility problem with label option from tikz
	- Fixed resizing problem for shape ground
	- Variable capacitor
	- polarized capacitor
	- ConTeXt support (read the manual!)
	- nfet, nigfete, nigfetd, pfet, pigfete, pigfetd (contribution of Clemens Helfmeier and Theodor 
Borsche)
	- njfet, pjfet (contribution of Danilo Piazzalunga)
	- pigbt, nigbt
	- *backward incompatibility* potentiometer is now the standard resistor-with-arrow-in-the-middle; the old potentiometer is now known as variable resistor (or vR), similarly to variable inductor and variable capacitor
	- triac, thyristor, memristor
	- new property "name" for bipoles
	- fixed voltage problem for batteries in american voltage mode
	- european logic gates
	- *backward incompatibility* new american standard inductor. Old american inductor now called "cute inductor"
	- *backward incompatibility* transformer now linked with the chosen type of inductor, and version with core, too. Similarly for variable inductor
	- *backward incompatibility* styles for selecting shape variants now end are in the plural to avoid conflict with paths
	- new placing option for some tripoles (mostly transistors)
	- mirror path style

		
* Version 0.2.2 - 20090520
    - Added the shape for lamps.
	- Added options \texttt{europeanresistor}, \texttt{europeaninductor}, \texttt{americanresistor} and \texttt{americaninductor}, with corresponding styles.
	- FIXED: error in transistor arrow positioning and direction under negative \texttt{xscale} and \texttt{yscale}.

* Version 0.2.1 - 20090503
	- Op-amps added
	- added options arrowmos and noarrowmos, to add arrows to pmos and nmos

* Version 0.2 - 20090417
First public release on CTAN
   	- *Backward incompatibility*: labels ending with \texttt{:}\textit{angle} are not parsed for positioning anymore.
	- Full use of \TikZ\ keyval features.
	- White background is not filled anymore: now the network can be drawn on a background picture as well.
	- Several new components added (logical ports, transistors, double bipoles, \ldots).
	- Color support.
	- Integration with {\ttfamily siunitx}.
	- Voltage, american style.
	- Better code, perhaps. General cleanup at the very least.

* Version 0.1 - 2007-10-29
First public release
