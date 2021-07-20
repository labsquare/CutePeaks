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
Cutepeaks is a standalone Sanger trace viewer steered by a modern and user-friendly UI. Unlike other software, CutePeaks comes with two new features: searching for a regular expression and exporting the traces to svg.    
CutePeaks is available for Linux, MacOS and Windows at [https://labsquare.github.io/CutePeaks/](https://labsquare.github.io/CutePeaks/).

# Statement of need
Despite the major use of Next Generation Sequencing, the Sanger method is still widely used in genetic labs as the gold standard to read target DNA sequences. Very few opensource software is available to explore Sanger trace data and most of labs staff still rely on proprietary software. Moreover, they are not always user-friendly and lack modern look and feel. 

# State of fields
4peaks[@4Peaks] is a software widely used by biologists that benefits from a nice User interface. Sadly, it is only available on MacOS and source code is not opened to community enhancement. Seqtrace[@seqtrace] is the only standalone and opensource application we could find. However, it is written with GTK framework in Python 2, the latter being deprecated and slower than C++. 

# Software overview
![CutePeaks screenshot with regular expression search bar.\label{fig:example}](figure.png)

CutePeaks is a cross-platform application implemented in C++ using the open source Qt5 framework. It can read FSA and ABIF file formats, and display the chromatogram with standard controllers.
The chromatogram is displayed in an interactive window allowing the user to move along the trace. It can also re-scale dynamically the plot using two slider controllers. Finger gestures are also available for scrolling upon using a touch screen.
Similarily to 4peaks software[@4Peaks], Phred quality scores are displayed behind the trace as a blue histogram. Base calling is displayed at the top of the viewing window, along with adjustable amino-acid translation.
The trace can be used as with a text editor. Navigating along the trace, copying the sequence to the clipboard or cutting it is done using standard keyboard shortcuts. Revert/complement is also possible.
An original feature of CutePeaks is the possibility to search for a sequence in the trace using a regular expression. This is especially useful to search for a sequence pattern. Finally, the trace data can be exported to different formats, such as FASTA or SVG image, the latter being particularly useful for resolution-independent illustration.


# Installation

CutePeaks is hosted on the GitHub development platform. Continuous integration is provided by GitHub Actions.
For Linux, an AppImage is provided that is distribution agnostic and runs out of the box.
For Windows, a 32 bits binary compiled with mingw is provided and can be executed as a standalone application without administrator privileges. For MacOS, a disk image is provided.

# Acknowledgements

We acknowledge contributions from Anne-Sophie Denommé-Pichon, Jérémie Roquet, and Francisco Pina-Martins.

# References
