---
title: 'CutePeaks : A viewer for sanger trace file'
tags:
  - C++
  - Qt
  - biology
  - sanger
  - dna
  - sequencing
authors:
  - name: Sacha Schutz
    orcid: 0000-0002-4563-7537
    affiliation: "1, 2" 
  - name: Author Without ORCID
    affiliation: 2
  - name: Author with no affiliation
    affiliation: 3
affiliations:
 - name: Inserm, Univ Brest, EFS, UMR 1078, GGB, F-29200 Brest, France
   index: 1
 - name: Laboratoire de Génétique Moléculaire, CHU Brest
   index: 2
 - name: Independent Researcher
   index: 3
date: 13 August 2017
bibliography: paper.bib

---

# Summary

Despite the major use of Next Generation sequencing, The Sanger chromatograms method is still commonly used in laboratories as a gold standard to read target dna sequence. Two binary file format, ABIF and FSA, are used to store raw output of a Sanger experiment. Unfortunally few opensource software with a friendly user interface exists to manage these file. Let's note for example Seqtrace.

CutePeaks is a cross plateform Sanger Trace file viewer written in C++ with  Qt5 framework. It was inspired by 4peaks, which is source closed and works on Mac OS only. It can handle ABIF and FSA file and provide some improvement like geasture controls or regular expression pattern finder. 
Cutepeaks has been packages for Windows, Mac and Linux and is therefore easy to install. 

# Features
Cutepeaks loads trace data from one file into a dynamic view and provide different controller to manipulate it.
You can move along the trace using the scrollbar or using finger geasture if a touch screen is avaible. Slider control are avaible on bottom left to rescale the trace horizontally of vertically.
As a texteditor, you can create a selection of the trace using standard shortcut (CTRL+A, SHIFT+click) and copy the selected sequence to the clipboard using (CTRL+C). It is also possible to remove a selection using DEL shortcut. This is particulary usefull to remove noise data often visible at the end of the trace. 
To find a subsequence in the trace file, there is search bar activable with CTRL+F shortcut which allow to look over a regular expression pattern. For instance, the pattern A(CG)T will look for all instance of ACT or AGT. 
A last feature is the possbility to reverse and complement the trace file using (CTRL+I).
All of these actions can be reverted using undo / redo actions thanks to QUndoStack.
Finally, the trace data can be exported into different text format or image format. Notably the SVG file format, which is particular usefull to get a resolution independant trace picture to use for illustation.

# Installation 



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
