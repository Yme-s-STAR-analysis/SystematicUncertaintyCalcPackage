# Systematic Uncertainty Calculation Package

* Author: Yige Huang

* Data: Sat. May 13, 2023

* Version: 1.0

## Guide

* Folders

1. `core`: Definitions and implements for base classes, including `Point`, `Source` and `System`, also a `FormatSystem` class for output a `LATEX` table.

2. `demo`: Some demos, enter this directory and `make` to have a quick experience.

3. `CumulantsSysErrMakeTable`: MUST use Yige's format of saving cumulant results. Indeed, is a larger demo of using this systematic uncertainty calculation package.

* How to run

1. See `demo` and `CumulantsSysErrMakeTable`.

2. `CumulantsSysErrMakeTable` shows a complecated usage, for beginners, please see `demo/testFormat.cxx` and follow this guide:

> Initilize points `Point` with value, error and tag. You need a default point, and many varied points.

> Initilize sources `Source` with many points. For each source, a default point is needed with `Source::SetDefault`, and varied points are also necessary with `Source::AddVaried`.

> After you have all the sources prepared, add them to the `System`. Using `System::AddSource`.

> The `FormatSystem` class can make a LATEX table with 9 centrality points, which means you will need to prepare 9 `System` instances and add them to the `FormatSystem` with `Formatsystem::LoadSystem`.

> When everything above is done, use `FormatSystem::Print` to save the code of LATEX table.

3. The documents of this package are not yet finished, will get it updated soon.

## Notes

1. Before you output the LATEX table, please remember to call `System::GetSigma`. Then system-wise, source-wise and point-wise errors will all got calculated.

2. You can choose to turn on or turn off Barlow check (source level), please use `Source(const char*, int, bool)` constructor instead of `Source()`.

3. The output format can be changed with `FormatSystem::SetFormat`, the default argument is `%.4f`. 

## Change Logs

* 13.05.2023 yghuang v1.1:

> New feature: not only ouput LATEX table codes, but also create root files.

* 13.05.2023 yghuang v1.0:

> First version, all the fundamental functions are implemented.
