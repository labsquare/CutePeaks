---
title: 'Cutepeaks: A simple viewer for sanger trace file'
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

affiliations:
 - name: CHRU Brest 29200, Brest, France
   index: 1
 - name: Univ Brest, Inserm, EFS, UMR 1078, GGB, 29200
   index: 2

date: 15 June 2021
bibliography: paper.bib

---

# Summary

Despite the major use of Next Generation Sequencing, the Sanger method is still widely used in laboratories as the gold standard to read target DNA sequences. Raw output data of Sanger experiments are stored in files encoded with the ABIF and FSA binary formats. In the present note, we introduce an original Sanger trace viewer steered by a user-friendly graphic interface. The source code is distributed under GNU GPL License.

# Software overview
CutePeaks is a modern standalone cross-platform GUI (Graphical User Interface) application implemented in C++ within the open source Qt5 framework. It can read FSA and ABIF file formats, provides a customized parser and displays  the chromatogram with different controllers and a traditional aesthetic.
The chromatogram is displayed in an interactive window allowing the user to move along the trace or re-scale dynamically the plot using two slider controllers. Finger gestures are also available for scrolling upon using a touch screen.
Similarily to 4peaks, Phred quality scores are displayed behind the trace as a blue histogram. Base calling from the trace with adjustable amino-acid translation is displayed at the top of the viewing window.
The trace can be used as with a text editor. The user can select an area and copy it to the clipboard, or remove it from the trace . It is also possible to revert the full trace by applying a revert/complement transformation.
An original feature of CutePeaks is the possibility to search for a sequence in the trace with a regular expression. This is especially useful to serach for a sequence pattern.
For example, the query "A(CG)T" will search for all instances of ACT or AGT. The query AC.+T will select all instances of the form ACT, ACCT, ACCCCT etc.
Finally, the trace data can be exported into a text format (FASTA) or into a SVG image format, which provides for illustration a resolution independent trace picture.

# Mathematics

Single dollars ($) are required for inline mathematics e.g. $f(x) = e^{\pi/x}$

Double dollars make self-standing equations:

$$\Theta(x) = \left\{\begin{array}{l}
0\textrm{ if } x < 0\cr
1\textrm{ else}
\end{array}\right.$$

You can also use plain \LaTeX for equations
\begin{equation}\label{eq:fourier}
\hat f(\omega) = \int_{-\infty}^{\infty} f(x) e^{i\omega x} dx
\end{equation}
and refer to \autoref{eq:fourier} from text.

# Citations

Citations to entries in paper.bib should be in
[rMarkdown](http://rmarkdown.rstudio.com/authoring_bibliographies_and_citations.html)
format.

If you want to cite a software repository URL (e.g. something on GitHub without a preferred
citation) then you can do it with the example BibTeX entry below for @fidgit.

For a quick reference, the following citation commands can be used:
- `@author:2001`  ->  "Author et al. (2001)"
- `[@author:2001]` -> "(Author et al., 2001)"
- `[@author1:2001; @author2:2001]` -> "(Author1 et al., 2001; Author2 et al., 2002)"

# Figures

Figures can be included like this:
![Caption for example figure.\label{fig:example}](figure.png)
and referenced from text using \autoref{fig:example}.

Figure sizes can be customized by adding an optional second parameter:
![Caption for example figure.](figure.png){ width=20% }

# Acknowledgements

We acknowledge contributions from Brigitta Sipocz, Syrtis Major, and Semyeong
Oh, and support from Kathryn Johnston during the genesis of this project.

# References