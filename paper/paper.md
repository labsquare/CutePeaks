---
title: 'Cutepeaks: A modern viewer for Sanger trace file'
tags:
  - Python
  - Sanger
  - genetics
  - Qt
  - GUI
authors:
  - name: Sacha Schutz^[co-first author] # note this makes a footnote saying 'co-first author'
    orcid: 0000-0002-4563-7537
    affiliation: "1,2" # (Multiple affiliations must be quoted)
  - name: Charles Monod-Broca^[co-first author]
    orcid: 0000-0003-4095-8099
    affiliation: "2"

affiliations:
 - name: CHRU Brest 29200, Brest, France
   index: 1
 - name: Univ Brest, Inserm, EFS, UMR 1078, GGB, 29200
   index: 2

date: 15 June 2021
bibliography: paper.bib

---

# Summary

Despite the major use of Next Generation Sequencing, the Sanger method is still widely used in genetic labs as the gold standard to read target DNA sequences. Raw output data of Sanger experiments are stored in files encoded with the ABIF and FSA binary formats. In the present note, we introduce an original Sanger trace viewer steered by a modern and user-friendly graphical interface. Unlike other software, CutePeaks comes with two new features: searching for a regular expression and exporting the traces to svg.    
CutePeaks is available as a standalone application for Linux, MacOS and Windows at [https://labsquare.github.io/CutePeaks/](https://labsquare.github.io/CutePeaks/).


# Software overview
![CutePeaks screenshot with regular expression search bar.\label{fig:example}](figure.png)

CutePeaks is a modern standalone cross-platform GUI (Graphical User Interface) application implemented in C++ using the open source Qt5 framework. It can read FSA and ABIF file formats, and display the chromatogram with standard controllers.
The chromatogram is displayed in an interactive window allowing the user to move along the trace. It can also re-scale dynamically the plot using two slider controllers. Finger gestures are also available for scrolling upon using a touch screen.
Similarily to 4peaks software[@4Peaks], Phred quality scores are displayed behind the trace as a blue histogram. Base calling is displayed at the top of the viewing window, along with adjustable amino-acid translation.
The trace can be used as with a text editor using standard keyboard shortcuts. The user can select an area and copy it to the clipboard, as well as cutting parts of the trace. It is also possible to revert the full trace by applying a revert/complement transformation.
An original feature of CutePeaks is the possibility to search for a sequence in the trace using a regular expression. This is especially useful to search for a sequence pattern. For example, the query `A[CG]T` will search for all instances of `ACT` or `AGT`. The query `AC.+T` will select all instances of the form `ACT`, `ACCT`, `ACCCCT` etc.
Finally, the trace data can be exported to different formats, such as FASTA or SVG image, the latter being particularly useful for resolution-independent illustration.


# Installation

CutePeaks is hosted on the GitHub development platform. Continuous integration is provided by GitHub Actions.
For Linux, an AppImage is provided that is distribution agnostic and runs out of the box.
For Windows, a 32 bits binary compiled with mingw is provided and can be executed as a standalone application without administrator privileges.
For MacOS, a disk image is provided.

# Further Improvement
The C++ Tracy [@Tracy] library has been published recently and is intended for alignment and assembly of Sanger electrophoregram traces data. This library could then be integrated into cutepeaks in order to benefit from its new features. 

# Acknowledgements

We acknowledge contributions from Anne-Sophie Denommé-Pichon, Jérémie Roquet, and Francisco Pina-Martins.

# References
