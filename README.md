# eink-xplained-pro-asf3

## Introduction

Eink Xplained Pro AFS3 Software Library with example projects for use with Microchip SAM MCUs.

This software library is designed to work with the following displays and driver ICs:

- ED029TC1 : UC8151
- *HINK-E0154A05 : SSD1608 (not yet implemented)*
- ED057TC2 : UC8159 (not yet implemented)

It also includes several open source fonts in varying sizes and weights.

Note that the software library and each example project has a **doxygen** folder with documentation inside (open *doxygen.html* to get started).

#### Note
> The library only allows a single display to be connected to the MCU.

## Usage 

The folder structure should be maintained after download as the example projects use relative paths to reference the software library. Note as well that the repository should be downloaded to your root C: folder as the folder structure can cause Windows to produce errors such as:
> The source file name(s) are larger than is supported by the file system

## Product Support

Note that Microchip has ended development for the ASF3 software library, but is currently continuing to support it. With this in mind, the Eink Software Library only supports a range of Microchip devices but an ASF4 Eink Library is currently under development to bridge this gap. At present the ASF3 Eink Software Library supports any MCUs that make use of the ASF3 IOPORT Service. There are a number of example projects to show the different chips that are supported:
- [SAM4E](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_sam4e_ed029tc1_1_1)
- [SAM4S](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_sam4s_ed029tc1_1_1)
- [SAMD20](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_samd20_ed029tc1_1_1)
- [SAMD21](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_samd21_ed029tc1_1_1)
- [SAMG55](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_samg55_ed029tc1_1_1)
- [SAML21A](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_saml21a_ed029tc1_1_1)
- [SAML21B](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_saml21b_ed029tc1_1_1)
- [SAMV71](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_samv71_ed029tc1_1_1)
- [SAMW25](https://github.com/Ineltek-UK/eink-xplained-pro-asf3/tree/master/example_projects/eink_asf3_1_1/eink_xplained_samw25_ed029tc1_1_1)

## Compilation Information

This software was written for the GNU GCC compiler using Atmel Studio 7.0 and requires ASF version 3 (originally compiled using ASF version 3.42.0). Other compilers may or may not work.